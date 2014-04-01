Feature:
  All Mobile4Social Demo tests

  @api @all
  Scenario: Test basic installation
    Given I am logging in as "admin"
     Then I should see the menu item "Drupal of Things" before "Content"
