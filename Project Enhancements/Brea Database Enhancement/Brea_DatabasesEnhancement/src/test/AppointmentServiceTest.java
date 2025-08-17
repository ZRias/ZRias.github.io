package test;

import static org.junit.jupiter.api.Assertions.*;

import java.util.Date;

import org.junit.jupiter.api.Test;

import src.AppointmentService;

class AppointmentServiceTest extends BaseTest {
	
	final int AnHourInMilliseconds = 3600000;
	
	
	
	String testID = "12345";
	Date AnHourInTheFuture = new Date(System.currentTimeMillis() + AnHourInMilliseconds);
	String testDescription = "This is the description for the appointment";
	
	String testID2 = "55555";
	String testID3 = "999999";
	Date AnHourInThePast = new Date(System.currentTimeMillis() - AnHourInMilliseconds);
	Date TwoHoursInTheFuture = new Date(System.currentTimeMillis() + (2 * AnHourInMilliseconds));
	Date ThreeHoursInTheFuture = new Date(System.currentTimeMillis() + (3 * AnHourInMilliseconds));
	String testDescription2 = "New Description for test";

	@Test
	void testAddAppointmentToService() {
		
		AppointmentService app = new AppointmentService();
		
		app.addAppointment(testID, AnHourInTheFuture, testDescription);
		
		assertAll("Should add appointment to app with no errors",
				() -> assertTrue(app.getAppointment(testID).getAppID().equals(testID)),
				() -> assertTrue(app.getAppointment(testID).getDate().equals(AnHourInTheFuture)),
				() -> assertTrue(app.getAppointment(testID).getDesc().equals(testDescription)));
	}
	
	@Test
	void testDeleteAppointmentFromService() {
		
		AppointmentService app = new AppointmentService();
		app.addAppointment(testID, AnHourInTheFuture, testDescription);
		app.addAppointment(testID2, TwoHoursInTheFuture, testDescription);
		app.addAppointment(testID3, ThreeHoursInTheFuture, testDescription);
		
		app.deleteAppointment(testID2);
		
		assertThrows(NullPointerException.class, () -> {
			app.getAppointment(testID2).getAppID().equals(testID2);
		});
	}
	
	@Test
	void testIDNull() {
		AppointmentService app = new AppointmentService();
		
		assertThrows(IllegalArgumentException.class, () -> {
			app.addAppointment(null, AnHourInTheFuture, testDescription);
		});
	}
	
	@Test
	void testIDEmpty() {
		AppointmentService app = new AppointmentService();
		
		assertThrows(IllegalArgumentException.class, () -> {
			app.addAppointment("", AnHourInTheFuture, testDescription);
		});
	}
	
	@Test
	void testUpdateAppointment() {
		AppointmentService app = new AppointmentService();
		
		app.addAppointment(testID, AnHourInTheFuture, testDescription);
		
		app.updateAppointment(testID, TwoHoursInTheFuture, testDescription2);
		
		assertAll("Should update appointment to app with no errors",
				() -> assertTrue(app.getAppointment(testID).getAppID().equals(testID)),
				() -> assertTrue(app.getAppointment(testID).getDate().equals(TwoHoursInTheFuture)),
				() -> assertTrue(app.getAppointment(testID).getDesc().equals(testDescription2)));
		}
		

}
