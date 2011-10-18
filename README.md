Entity Base for Drupal 7.x
========================
Drupal module which provides a base class which can be used by other modules to provide simple access to entity fields.

This module basically does nothing initially. Other modules should extend the EntityBase\EntityBase class to provide its functionality for a specific entity type.

See:

* Node Wrapper (https://github.com/korstiaan/nodewrapper)
* User Wrapper (https://github.com/korstiaan/userwrapper)

Requirements
--------------------------------

* Drupal 7.x
* PHP 5.3.2 or higher
* Namespace Autoload (https://github.com/korstiaan/nsautoload)

Setup / Initial Installation
--------------------------------

Install it as a normal Drupal module. This means downloading (or git clone'ing) it to site/all/modules and enabling it on "admin/modules/list".

If you're using Voiture (http://voiture.hoppinger.com) just add "entitybase" to cnf/shared/modules.php
