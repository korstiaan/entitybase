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

interface EntityInterface 
{
	/** 
	 * 
	 * Returns the value of given field
	 * 
	 * @param 	string 		$field
	 * @return	mixed		
	 */
	public function get($field);

	/** 
	 * 
	 * Sets the value of given field to given val
	 * 
	 * @param 	string			$field
	 * @param 	mixed 			$val
	 * @return	EntityInterface	this
	 */
	public function set($field,$val);
	
	/**
	 * 
	 * Returns the id of the entity 
	 * 
	 * @return	integer|boolean
	 */
	public function getId();
	
	/**
	 * 
	 * Returns the drupal entity object
	 * 
	 * @return	\stdClass
	 */
	public function getEntity();
	
	/**
	 * 
	 * Returns the entity type for the entity
	 * 
	 * @return		string
	 */
	public function getEntityType();
	/**
	 * 
	 * Saves the entity to the db
	 * 
	 * @return	void
	 */
	public function save();
	
	/**
	 * 
	 * Returns the language
	 * 
	 * @return	string
	 */
	public function getLanguage();
	public function isValidField($field);
}
