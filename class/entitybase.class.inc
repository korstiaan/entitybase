<?php
/**
 *	Entity Base
 *  Copyright (C) 2011  Korstiaan de Ridder <korstiaan [at] korstiaan.com>
 *
 *	This file is part of Entity Base.
 *
 *  Entity Base is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Entity Base is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Entity Base.  If not, see <http://www.gnu.org/licenses/>.
 */
namespace EntityBase;

abstract class EntityBase implements EntityInterface 
{
	/**
	 * 
	 * The drupal entity
	 * 
	 * @var \stdClass
	 */
	private 	$entity 	= null;
	
	/**
	 *
	 * Language identifier
	 * 
	 * @var 	string
	 */
	protected 	$lang 		= null;
	
	/**
	 * 
	 * Cache of the requested field instancnes
	 * 
	 * @var 	array[EntityFieldInterface]
	 */
	private		$fields		= array();
	
	/**
	 * 
	 * Stores all valid fields of the entity
	 * 
	 * @var 	array
	 */
	protected	$typeFields	= null;
	
	/**
	 * 
	 * Ctor
	 * 
	 * @param 		\stdClass 		$entity 		the entity to wrap
	 * @param 		string 			$language		the language to do the magic in
	 *   
	 */
	public function __construct(\stdClass $entity,$language = LANGUAGE_NONE)
	{
		$this->entity 	= $entity;
		$this->lang 	= $language;
	}
	
	/**
	 * @see EntityBase.EntityInterface::get()
	 * @see EntityBase.EntityFieldInterface::get()
	 */
	public function get($field)
	{
		return $this->getField($field)->get();
	}
	
	/**
	 * @see		EntityBase.EntityInterface::set()
	 * @see 	EntityBase.EntityFieldInterface::set()
	 * 
	 * @return	EntityInterface
	 */
	public function set($field,$val)
	{
		$this->getField($field)->set($val);
		return $this;
	}
	
	
	public function isValidField($field)
	{
		return in_array($field,$this->getValidFields(),true);
	}
	
	/**
	 * 
	 * Returns entity properties which aren't actual fields.
	 * 
	 * @return	array
	 */
	abstract protected function getBaseFields();
	
	/**
	 * 
	 * Returns bundle name for this instance.
	 *
	 * @return	string
	 */
	abstract protected function getBundleName();
	
	/**
	 * Returns all valid fields for this entity.
	 * 
	 * These are:
	 *  - Base fields (non "field" properties)
	 *  - Field instances for this entity. 
	 * 
	 * @return		array
	 */
	protected function getValidFields()
	{
		if (is_null($this->typeFields)) {
			$this->typeFields = array_merge(
				$this->getBaseFields(),
				array_keys((array)field_info_instances($this->getEntityType(),$this->getBundleName()))
			);
		}
		return $this->typeFields;
	}
	
	/**
	 * 
	 * @param 	string 					$field
	 * @return	EntityFieldInterface
	 */
	protected function getField($field)
	{
		if (!$this->isValidField($field)) {
			throw new \InvalidArgumentException("Invalid field {$field} for this bundle");
		}
		if (!isset($this->fields[$field])) {
			$this->fields[$field] = new EntityField($field, $this);
		}
		return $this->fields[$field];
	}
	
	/**
	 * 
	 * Returns the entity
	 * 
	 * @see 		EntityBase.EntityInterface::getEntity()
	 * 
	 * @return		\stdClass			the entity
	 */
	public function getEntity()
	{
		return $this->entity;
	}
	
	/**
	 * @see 		EntityBase.EntityInterface::getLanguage()
	 * 
	 * @return		string
	 */
	public function getLanguage()
	{
		return $this->lang;
	}
}