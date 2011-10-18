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

interface EntityFieldInterface
{
	/**
	 * 
	 * Returns the field value for this entity instance
	 * 
	 * @return 		mixed
	 */
	public function get();
	/**
	 * 
	 * Sets field value to given val 
	 * 
	 * @param 	mixed 	$val
	 */
	public function set($val);
	
	/**
	 * 
	 * Returns the entity instance of this field
	 * 
	 * @return 	EntityInterface
	 */
	public function getWrappedEntity();
	
	/**
	 * 
	 * Returns the field name
	 * 
	 * @return	string
	 */
	public function getName();
}
