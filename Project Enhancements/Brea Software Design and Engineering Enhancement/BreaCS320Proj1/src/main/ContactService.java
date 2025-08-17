package main;

import java.util.HashMap;

public class ContactService {
	//collection of contacts with iD as key for easy access
	private HashMap<String, Contact> service = new HashMap<String, Contact>();
	
	//add Contact to collection
	public void addContact(String iD, String firstName, String lastName, String phone, String address) {
		//check iD before setting it
		if (iD.length() > 10 || iD == null) {
			throw new IllegalArgumentException("Invalid ID");
		}
		
		//create contact object
		Contact entry = new Contact(iD, firstName, lastName, phone, address);
		
		//add to map
		service.put(iD, entry);
	}
	
	//remove from map based on iD
	public void removeContact(String iD) {
		service.remove(iD);
	}
	
	//set firstName based on iD
	public void updateContactFirstName(String iD, String firstName) {
		service.get(iD).setFirstName(firstName);
	}
	
	//set lastName based on iD
	public void updateContactLastName(String iD, String lastName) {
		service.get(iD).setLastName(lastName);
	}
	
	//set phone based on iD
	public void updateContactPhone(String iD,String phone) {
		service.get(iD).setPhone(phone);
	}
	
	//set address based on iD
	public void updateContactAddress(String iD, String address) {
		service.get(iD).setAddress(address);
	}
	
	//get contact based on iD
	public Contact getContact(String iD) {
		return service.get(iD);
	}
	
}
