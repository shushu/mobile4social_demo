<?php

use Drupal\DrupalExtension\Context\DrupalContext;
use Behat\Behat\Context\Step\Given;
use Behat\Gherkin\Node\TableNode;
use Behat\Gherkin\Node\PyStringNode;
use Guzzle\Service\Client;
use Behat\Behat\Context\Step;
use Behat\Behat\Context\Step\When;

require 'vendor/autoload.php';

class FeatureContext extends DrupalContext {
  /**
   * Hold the user name and password for the selenium tests for log in.
   */
  private $users;

  /**
   * Initializes context.
   *
   * Every scenario gets its own context object.
   *
   * @param array $parameters.
   *   Context parameters (set them up through behat.yml or behat.local.yml).
   */
  public function __construct(array $parameters) {
    if (isset($parameters['drupal_users'])) {
      $this->users = $parameters['drupal_users'];
    }
    else {
      throw new Exception('behat.yml should include "drupal_users" property.');
    }
  }

  /**
   * Authenticates a user with password from configuration.
   *
   * @Given /^I am logging in as "([^"]*)"$/
   */
  public function iAmLoggingInAs($username) {

    try {
      $password = $this->users[$username];
    }
    catch (Exception $e) {
      throw new Exception("Password not found for '$username'.");
    }

    if ($this->getDriver() instanceof Drupal\Driver\DrushDriver) {
      // We are using a cli, log in with meta step.

      return array(
        new Step\When('I am not logged in'),
        new Step\When('I visit "/user"'),
        new Step\When('I fill in "Username" with "' . $username . '"'),
        new Step\When('I fill in "Password" with "' . $password . '"'),
        new Step\When('I press "edit-submit"'),
      );
    }
    else {
      // Log in.
      // Go to the user page.
      $element = $this->getSession()->getPage();
      $this->getSession()->visit($this->locatePath('/user'));
      $element->fillField('Username', $username);
      $element->fillField('Password', $password);
      $submit = $element->findButton('Log in');
      $submit->click();
    }
  }

  /**
   * @Then /^I should see the text "([^"]*)" under "([^"]*)"$/
   */
  public function iShouldSeeTheTextUnder($text, $container) {
    if (!$this->searchForTextUnderElement($text, $container)) {
      throw new Exception(sprintf("The element with %s was not found in %s", $text, $container));
    }
  }

  /**
   * Searching text under an element with class
   */
  private function searchForTextUnderElement($text, $container) {
    $page = $this->getSession()->getPage();
    $element = $page->find('xpath', "//*[contains(@id, '{$container}')]//*[contains(., '{$text}')]");
    return $element;
  }
}
