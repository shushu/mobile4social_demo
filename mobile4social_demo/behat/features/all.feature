Feature:
  All Mobile4Social Demo tests

  @api @all
  Scenario: Test basic installation
    Given I am logging in as "admin"
     Then I should see the text "Drupal of Things" under "admin-menu"
