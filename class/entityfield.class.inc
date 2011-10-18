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

class EntityField implements EntityFieldInterface
{
	private $field 		= null;
	private $wrapper 	= null;
	
	/**
	 * 
	 * Ctor 
	 * 
	 * @param string 			$field
	 * @param EntityInterface 	$wrapper
	 */
	public function __construct($field, EntityInterface $wrapper) 
	{
		if (!$wrapper->isValidField($field)) {
			throw new \InvalidArgumentException("Invalid field {$field} for this bundle");
		}
		$this->field 	= $field;
		$this->wrapper 	= $wrapper;
	}
	
	/**
	 * @see 		EntityBase.EntityFieldInterface::getWrappedEntity()
	 * @return		EntityInterface
	 */
	public function getWrappedEntity()
	{
		return $this->wrapper;
	}
	
	/**
	 * @see EntityBase.EntityFieldInterface::getName()
	 */
	public function getName()
	{
		return $this->field;
	}
	
	/**
	 * 
	 * Returns some useful field info so we can do our get/set magic
	 * 
	 * @param 	string 	$field
	 * @return	array
	 */
	protected function getInfo()
	{
		
		$info = field_info_field($this->getName());
		
		return array(
			'name'		=> $this->getName(),
			'columns'	=> isset($info['columns']) && !empty($info['columns']) ? array_keys($info['columns']) : false,
			'single'	=> !isset($info['cardinality']) || $info['cardinality'] == 1,
			'lang'		=> field_language($this->getWrappedEntity()->getEntityType(),$this->getWrappedEntity()->getEntity(),$this->getName(),$this->getWrappedEntity()->getLanguage()),
			'data'		=> $info,			
		);
		
	}
	
	/**
	 * 
	 * Returns the value of this field. This is either:
	 *  - if field not set or empty 			: null 
	 *  - if field has cardinality > 1			: array of mixed 
	 *  - if field has cardinality of 1 		: mixed
	 *  
	 * @see 		EntityBase.EntityFieldInterface::get()
	 * @return		mixed
	 */
	public function get()
	{
		if (!isset($this->getWrappedEntity()->getEntity()->{$this->getName()})) return null;
		
		$info = $this->getInfo();
		
		if (!empty($info['data'])) {
			if (!isset($this->getWrappedEntity()->getEntity()->{$this->getName()}[$info['lang']]) || empty($this->getWrappedEntity()->getEntity()->{$this->getName()}[$info['lang']])) return null;
			
			$vals = array();
			foreach ($this->getWrappedEntity()->getEntity()->{$this->getName()}[$info['lang']] as $val) {
				$vals[] = is_array($val) && count($info['columns']) <= 1 ? reset($val) : $val;
			}
			
			return $info['single'] ? reset($vals) : $vals;				
		} else {
			return $this->getWrappedEntity()->getEntity()->{$this->getName()};
		}

		return null;
	}
	
	/**
	 * 
	 * Sets the value of this field to given val.
	 * 
	 * @see 		EntityBase.EntityFieldInterface::set()
	 * 
	 * @param		mixed			$val
	 */
	public function set($val)
	{
		$info = $this->getInfo();
		
		if ($info['columns'] !== false) {
			 
			if ($info['single']) {
				$vals = array($this->getValueArray($val));
			} else {
				if (!is_array($val)) {
					throw new \InvalidArgumentException('Field has cardinality > 1, so please supply an array');
				}
				$vals = array();
				foreach ($val as $v) {
					$vals[] = $this->getValueArray($v);					
				}
			}
			$this->getWrappedEntity()->getEntity()->{$this->getName()} = array($info['lang'] => $vals);
			
		} else {
			$this->getWrappedEntity()->getEntity()->{$this->getName()} = $val; 
		}
	}
	
	/**
	 * 
	 * Converts given value to a valid single value array drupal expects. 
	 * 
	 * @throws 	\InvalidArgumentException	in case an column is expected but not valid for given field 
	 * 
	 * @param 	array 			$field
	 * @param 	mixed 			$val
	 * @return	array
	 */
	private function getValueArray($val)
	{
		$info = $this->getInfo();
		if (is_array($val)) {
			$diff = array_diff(array_keys($val),$info['columns']);
			if (!empty($diff)) { 
				throw new \InvalidArgumentException("Invalid columns set for field '{$info['name']}': ".implode(', ',$diff));
			} 
		} else {
			$val = array(reset($info['columns']) => $val);
		}
		return $val;
	}
	
}
