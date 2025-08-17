package test;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;

import main.ContactService;

class ContactServiceTest {

	@Test
	void testContactServiceAddContact() {
		ContactService contacts = new ContactService();
		contacts.addContact("12345", "Zach", "Brea", "1234567890", "123 Main St");
		assertAll("Should add Contact to contacts with no errors",
				() -> assertTrue(contacts.getContact("12345").getiD().equals("12345")),
				() -> assertTrue(contacts.getContact("12345").getFirstName().equals("Zach")),
				() -> assertTrue(contacts.getContact("12345").getLastName().equals("Brea")),
				() -> assertTrue(contacts.getContact("12345").getPhone().equals("1234567890")),
				() -> assertTrue(contacts.getContact("12345").getAddress().equals("123 Main St")));
	}
	
	@Test
	void testContactServiceIDNull() {
		ContactService contacts = new ContactService();
		Assertions.assertThrows(IllegalArgumentException.class, () -> {
			contacts.addContact("", "Zach", "Brea", "1234567890", "123 Main St");
		});
	}
		
	@Test
	void testContactServiceIDTooLong() {
		ContactService contacts = new ContactService();
		Assertions.assertThrows(IllegalArgumentException.class, () -> {
			contacts.addContact("12345678901", "Zach", "Brea", "1234567890", "123 Main St");
		});
	}
	
	@Test
	void testContactServiceUpdateContactFirstName() {
		ContactService contacts = new ContactService();
		contacts.addContact("12345", "Zach", "Brea", "1234567890", "123 Main St");
		
		contacts.updateContactFirstName("12345", "Zachary");
		
		assertTrue(contacts.getContact("12345").getFirstName().equals("Zachary"));
	}
	
	@Test
	void testContactServiceUpdateContactLastName() {
		ContactService contacts = new ContactService();
		contacts.addContact("12345", "Zach", "Brea", "1234567890", "123 Main St");
		
		contacts.updateContactLastName("12345", "Bread");
		
		assertTrue(contacts.getContact("12345").getLastName().equals("Bread"));
	}
	
	@Test
	void testContactServiceUpdateContactPhone() {
		ContactService contacts = new ContactService();
		contacts.addContact("12345", "Zach", "Brea", "1234567890", "123 Main St");
		
		contacts.updateContactPhone("12345", "0987654321");
		
		assertTrue(contacts.getContact("12345").getPhone().equals("0987654321"));
	}
	
	@Test
	void testContactServiceUpdateContactAddress() {
		ContactService contacts = new ContactService();
		contacts.addContact("12345", "Zach", "Brea", "1234567890", "123 Main St");
		
		contacts.updateContactAddress("12345", "321 1st Ave");
		
		assertTrue(contacts.getContact("12345").getAddress().equals("321 1st Ave"));
	}
	
	@Test
	void testContactServiceDeleteContact() {
		ContactService contacts = new ContactService();
		contacts.addContact("12345", "Zach", "Brea", "1234567890", "123 Main St");
		
		contacts.removeContact("12345");
		
		assertThrows(NullPointerException.class, () -> {
			contacts.getContact("12345").getiD().equals("12345");
		});
	}

}
