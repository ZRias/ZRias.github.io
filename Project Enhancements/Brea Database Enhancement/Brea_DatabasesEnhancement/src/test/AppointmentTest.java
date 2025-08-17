package test;

import static org.junit.jupiter.api.Assertions.*;

import java.util.Date;

import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;

import src.Appointment;

class AppointmentTest {

	final int AnHourInMilliseconds = 3600000;
	
	Date AnHourInThePast = new Date(System.currentTimeMillis() - AnHourInMilliseconds);
	
	String testID = "12345";
	Date AnHourInTheFuture = new Date(System.currentTimeMillis() + AnHourInMilliseconds);
	String testDescription = "This is the description for the appointment";
	
	@Test
	void testAppointment() {
		
		Appointment appClass = new Appointment(testID, AnHourInTheFuture, testDescription);
		assertAll("Should initialize all variables of Appointment",
			() -> assertTrue(appClass.getAppID().equals(testID)),
			() -> assertTrue(appClass.getDate().equals(AnHourInTheFuture)),
			() -> assertTrue(appClass.getDesc().equals(testDescription)));
	}
	
	@Test
	void testDateBeforeCurrent() {
		assertThrows(IllegalArgumentException.class, () -> {
			new Appointment(testID, AnHourInThePast, testDescription);
		});
	}
	
	@Test
	void testDateNull() {
		assertThrows(IllegalArgumentException.class, () -> {
			new Appointment(testID, null, testDescription);
		});
	}
	
	@Test
	void testAppIDNull() {
		assertThrows(IllegalArgumentException.class, () -> {
			new Appointment(null, AnHourInTheFuture, testDescription);
		});
	}
	
	@Test
	void testAppIDTooLong() {
		assertThrows(IllegalArgumentException.class, () -> {
			new Appointment("12345678901", AnHourInTheFuture, testDescription);
		});
	}
	
	@Test
	void testAppIDEmpty() {
		assertThrows(IllegalArgumentException.class, () -> {
			new Appointment("", AnHourInTheFuture, testDescription);
		});
	}
	
	@Test
	void testDescNull() {
		assertThrows(IllegalArgumentException.class, () -> {
			new Appointment(testID, AnHourInTheFuture, null);
		});
	}
	
	@Test
	void testDescTooLong() {
		assertThrows(IllegalArgumentException.class, () -> {
			new Appointment(testID, AnHourInTheFuture, "This is the description for the appointment which is way too long for this object which will throw illegal argument");
		});
	}
	
	@Test
	void testDescEmpty() {
		assertThrows(IllegalArgumentException.class, () -> {
			new Appointment(testID, AnHourInTheFuture, "");
		});
	}
	
	@Test
	void testSetDesc() {
		Appointment appClass = new Appointment(testID, AnHourInTheFuture, testDescription);
		appClass.setDesc("Test Description");
		assertTrue(appClass.getDesc().equals("Test Description"));
	}
	
	@Test
	void testSetDate() {
		Date newDate = new Date(System.currentTimeMillis() + (2 * AnHourInMilliseconds));
		Appointment appClass = new Appointment(testID, AnHourInTheFuture, testDescription);
		appClass.setDate(newDate);
		assertTrue(appClass.getDate().equals(newDate));
	}
	
	@Test 
	void testSetDescNull() {
		Appointment appClass = new Appointment(testID, AnHourInTheFuture, testDescription);
		assertThrows(IllegalArgumentException.class, () -> {
			appClass.setDesc(null);
		});
	}
	
	@Test 
	void testSetDateNull() {
		Appointment appClass = new Appointment(testID, AnHourInTheFuture, testDescription);
		assertThrows(IllegalArgumentException.class, () -> {
			appClass.setDate(null);
		});
	}
	
	@Test
	void testSetDescTooLong() {
		Appointment appClass = new Appointment(testID, AnHourInTheFuture, testDescription);
		assertThrows(IllegalArgumentException.class, () -> {
			appClass.setDesc("This is the description for the appointment which is way too long for this object which will throw illegal argument");
		});
	}
	
	@Test
	void testSetDateBeforeCurrent() {
		Appointment appClass = new Appointment(testID, AnHourInTheFuture, testDescription);
		assertThrows(IllegalArgumentException.class, () -> {
			appClass.setDate(AnHourInThePast);
		});
	}
	
	@Test
	void testSetDescEmpty() {
		Appointment appClass = new Appointment(testID, AnHourInTheFuture, testDescription);
		assertThrows(IllegalArgumentException.class, () -> {
			appClass.setDesc("");
		});
	}
}
