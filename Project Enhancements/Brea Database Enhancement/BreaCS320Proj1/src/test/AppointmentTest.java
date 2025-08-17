package test;

import static org.junit.jupiter.api.Assertions.*;

import java.util.Date;

import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;

import main.Appointment;

class AppointmentTest {

	@Test
	void testAppointment() {
		/** 
		 * 1739275200000L is that many milliseconds after January 1 1970 which makes it February 11 2025 7 AM EST
		 * I did this just because it was easier to do it this way without using LocalDate since using 
		 * java.util.Date was required based on the instructions
		 */
		Appointment appClass = new Appointment("12345", new Date(1739275200000L), "This is the description for the appointment");
		assertAll("Should initialize all variables of Appointment",
			() -> assertTrue(appClass.getAppID().equals("12345")),
			() -> assertTrue(appClass.getDate().equals(new Date(1739275200000L))),
			() -> assertTrue(appClass.getDesc().equals("This is the description for the appointment")));
	}
	
	@Test
	void testDateBeforeCurrent() {
		//1730476800000L is November 1st 2024 at 12 P.M. EST
		assertThrows(IllegalArgumentException.class, () -> {
			new Appointment("12345", new Date(1730476800000L), "This is the description for the appointment");
		});
	}
	
	@Test
	void testDateNull() {
		assertThrows(IllegalArgumentException.class, () -> {
			new Appointment("12345", null, "This is the description for the appointment");
		});
	}
	
	@Test
	void testAppIDNull() {
		assertThrows(IllegalArgumentException.class, () -> {
			new Appointment(null, new Date(1739275200000L), "This is the description for the appointment");
		});
	}
	
	@Test
	void testAppIDTooLong() {
		assertThrows(IllegalArgumentException.class, () -> {
			new Appointment("12345678901", new Date(1739275200000L), "This is the description for the appointment");
		});
	}
	
	@Test
	void testAppIDEmpty() {
		assertThrows(IllegalArgumentException.class, () -> {
			new Appointment("", new Date(1739275200000L), "This is the description for the appointment");
		});
	}
	
	@Test
	void testDescNull() {
		assertThrows(IllegalArgumentException.class, () -> {
			new Appointment("12345", new Date(1739275200000L), null);
		});
	}
	
	@Test
	void testDescTooLong() {
		assertThrows(IllegalArgumentException.class, () -> {
			new Appointment("12345", new Date(1739275200000L), "This is the description for the appointment which is way too long for this object which will throw illegal argument");
		});
	}
	
	@Test
	void testDescEmpty() {
		assertThrows(IllegalArgumentException.class, () -> {
			new Appointment("12345", new Date(1739275200000L), "");
		});
	}
	
	@Test
	void testSetDesc() {
		Appointment appClass = new Appointment("12345", new Date(1739275200000L), "This is the description for the appointment");
		appClass.setDesc("Test Description");
		assertTrue(appClass.getDesc().equals("Test Description"));
	}
	
	@Test
	void testSetDate() {
		//1742486400000L = March 20 2025 12:00 PM EST
		Appointment appClass = new Appointment("12345", new Date(1739275200000L), "This is the description for the appointment");
		appClass.setDate(new Date(1742486400000L));
		assertTrue(appClass.getDate().equals(new Date(1742486400000L)));
	}
	
	@Test 
	void testSetDescNull() {
		Appointment appClass = new Appointment("12345", new Date(1739275200000L), "This is the description for the appointment");
		assertThrows(IllegalArgumentException.class, () -> {
			appClass.setDesc(null);
		});
	}
	
	@Test 
	void testSetDateNull() {
		Appointment appClass = new Appointment("12345", new Date(1739275200000L), "This is the description for the appointment");
		assertThrows(IllegalArgumentException.class, () -> {
			appClass.setDate(null);
		});
	}
	
	@Test
	void testSetDescTooLong() {
		Appointment appClass = new Appointment("12345", new Date(1739275200000L), "This is the description for the appointment");
		assertThrows(IllegalArgumentException.class, () -> {
			appClass.setDesc("This is the description for the appointment which is way too long for this object which will throw illegal argument");
		});
	}
	
	@Test
	void testSetDateBeforeCurrent() {
		//1730476800000L is November 1st 2024 at 12 P.M. EST
		Appointment appClass = new Appointment("12345", new Date(1739275200000L), "This is the description for the appointment");
		assertThrows(IllegalArgumentException.class, () -> {
			appClass.setDate(new Date(1730476800000L));
		});
	}
	
	@Test
	void testSetDescEmpty() {
		Appointment appClass = new Appointment("12345", new Date(1739275200000L), "This is the description for the appointment");
		assertThrows(IllegalArgumentException.class, () -> {
			appClass.setDesc("");
		});
	}
}
