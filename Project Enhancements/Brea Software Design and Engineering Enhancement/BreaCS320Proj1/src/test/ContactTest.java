package test;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;

import main.Contact;

class ContactTest {

	@Test
	void testContact() {
		Contact contactClass = new Contact("12345", "Zach", "Brea", "1234567890", "123 Main St");
		assertAll("Should initialize all variables of Contact",
			() -> assertTrue(contactClass.getiD().equals("12345")),
			() -> assertTrue(contactClass.getFirstName().equals("Zach")),
			() -> assertTrue(contactClass.getLastName().equals("Brea")),
			() -> assertTrue(contactClass.getPhone().equals("1234567890")),
			() -> assertTrue(contactClass.getAddress().equals("123 Main St")));
	}
	
	@Test
	void testContactSetters() {
		Contact contactClass = new Contact("12345", "Zach", "Brea", "1234567890", "123 Main St");
		contactClass.setFirstName("Jack");
		contactClass.setLastName("Johnson");
		contactClass.setPhone("0987654321");
		contactClass.setAddress("321 1st St");
		assertAll("Should initialize all variables of Contact",
			() -> assertTrue(contactClass.getFirstName().equals("Jack")),
			() -> assertTrue(contactClass.getLastName().equals("Johnson")),
			() -> assertTrue(contactClass.getPhone().equals("0987654321")),
			() -> assertTrue(contactClass.getAddress().equals("321 1st St")));
	}
	
	@Test
	void testContactiDTooLong() {
		Assertions.assertThrows(IllegalArgumentException.class, () -> {
			new Contact("12345678901", "Zach", "Brea", "1234567890", "123 Main St");
		});
	}
	
	@Test
	void testContactiDIsNull() {
		Assertions.assertThrows(IllegalArgumentException.class, () -> {
			new Contact(null, "Zach", "Brea", "1234567890", "123 Main St");
		});
	}
	
	@Test
	void testContactiDEmpty() {
		Assertions.assertThrows(IllegalArgumentException.class, () -> {
			new Contact("", "Zach", "Brea", "1234567890", "123 Main St");
		});
	}
	
	@Test
	void testContactFirstNameTooLong() {
		Assertions.assertThrows(IllegalArgumentException.class, () -> {
			new Contact("12345", "TooLongofAName", "Brea", "1234567890", "123 Main St");
		});
	}
	
	@Test
	void testContactFirstNameisNull() {
		Assertions.assertThrows(IllegalArgumentException.class, () -> {
			new Contact("12345", null, "Brea", "1234567890", "123 Main St");
		});
	}
	
	@Test
	void testContactFirstNameEmpty() {
		Assertions.assertThrows(IllegalArgumentException.class, () -> {
			new Contact("12345", "", "Brea", "1234567890", "123 Main St");
		});
	}
	
	@Test
	void testContactLastNameTooLong() {
		Assertions.assertThrows(IllegalArgumentException.class, () -> {
			new Contact("12345", "Zach", "TooLongofAName", "1234567890", "123 Main St");
		});
	}
	
	@Test
	void testContactLastNameisNull() {
		Assertions.assertThrows(IllegalArgumentException.class, () -> {
			new Contact("12345", "Zach", null, "1234567890", "123 Main St");
		});
	}
	
	@Test
	void testContactLastNameEmpty() {
		Assertions.assertThrows(IllegalArgumentException.class, () -> {
			new Contact("12345", "Zach", "", "1234567890", "123 Main St");
		});
	}
	
	@Test
	void testContactPhoneisNotTen() {
		Assertions.assertThrows(IllegalArgumentException.class, () -> {
			new Contact("12345", "Zach", "Brea", "1", "123 Main St");
		});
	}
	
	@Test
	void testContactPhoneisNull() {
		Assertions.assertThrows(IllegalArgumentException.class, () -> {
			new Contact("12345", "Zach", "Brea", null, "123 Main St");
		});
	}
	
	@Test
	void testContactPhoneEmpty() {
		Assertions.assertThrows(IllegalArgumentException.class, () -> {
			new Contact("12345", "Zach", "Brea", "", "123 Main St");
		});
	}
	
	@Test
	void testContactAddressTooLong() {
		Assertions.assertThrows(IllegalArgumentException.class, () -> {
			new Contact("12345", "Zach", "Brea", "1234567890", "123 Too Long of A Street Name For This Object");
		});
	}
	
	@Test
	void testContactAddressisNull() {
		Assertions.assertThrows(IllegalArgumentException.class, () -> {
			new Contact("12345", "Zach", "Brea", "1234567890", null);
		});
	}
	
	@Test
	void testContactAddressEmpty() {
		Assertions.assertThrows(IllegalArgumentException.class, () -> {
			new Contact("12345", "Zach", "Brea", "1234567890", "");
		});
	}
	
	@Test
	void testSettersNull() {
		Contact contactClass = new Contact("12345", "Zach", "Brea", "1234567890", "123 Main St");
		assertAll("Should all throw illegal argument exception",
			() -> assertThrows(IllegalArgumentException.class, () -> contactClass.setFirstName(null)),
			() -> assertThrows(IllegalArgumentException.class, () -> contactClass.setLastName(null)),
			() -> assertThrows(IllegalArgumentException.class, () -> contactClass.setPhone(null)),
			() -> assertThrows(IllegalArgumentException.class, () -> contactClass.setAddress(null)));
	}
	
}
