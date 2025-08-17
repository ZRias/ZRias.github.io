package test;

import static org.junit.jupiter.api.Assertions.*;

import java.util.Date;

import org.junit.jupiter.api.Test;

import main.AppointmentService;

class AppointmentServiceTest {

	@Test
	void testAddAppointmentToService() {
		//1739275200000L is February 11 2025 7 AM EST
		AppointmentService app = new AppointmentService();
		app.AddAppointment("12345", new Date(1739275200000L), "This is the Description");
		assertAll("Should add appointment to app with no errors",
				() -> assertTrue(app.getApp("12345").getAppID().equals("12345")),
				() -> assertTrue(app.getApp("12345").getDate().equals(new Date(1739275200000L))),
				() -> assertTrue(app.getApp("12345").getDesc().equals("This is the Description")));
	}
	
	@Test
	void testDeleteAppointmentFromService() {
		/*
		 * 1739275200000L is February 11 2025 7 AM EST
		 * 1742486400000L is March 20 2025 4 PM EST
		 * 1736182800000L is January 6 2025 12 PM EST
		 */
		AppointmentService app = new AppointmentService();
		app.AddAppointment("12345", new Date(1739275200000L), "This is the Description");
		app.AddAppointment("55555", new Date(1742486400000L), "This is the Description");
		app.AddAppointment("999999", new Date(1736182800000L), "This is the Description");
		
		app.DeleteAppointment("55555");
		
		assertThrows(NullPointerException.class, () -> {
			app.getApp("55555").getAppID().equals("55555");
		});
	}
	
	@Test
	void testIDNull() {
		//1739275200000L is February 11 2025 7 AM EST
		AppointmentService app = new AppointmentService();
		
		assertThrows(IllegalArgumentException.class, () -> {
			app.AddAppointment(null, new Date(1739275200000L), "This is the Description");
		});
	}
	
	@Test
	void testIDEmpty() {
		//1739275200000L is February 11 2025 7 AM EST
		AppointmentService app = new AppointmentService();
		
		assertThrows(IllegalArgumentException.class, () -> {
			app.AddAppointment("", new Date(1739275200000L), "This is the Description");
		});
	}
	
	@Test
	void testUpdateAppointment() {
		//1739275200000L is February 11 2025 7 AM EST
		//1742486400000L is March 20 2025 4 PM EST
		AppointmentService app = new AppointmentService();
		
		app.AddAppointment("12345", new Date(1739275200000L), "This is the Description");
		
		app.UpdateAppointment("12345", new Date(1742486400000L), "New Description for Test");
		
		assertAll("Should update appointment to app with no errors",
				() -> assertTrue(app.getApp("12345").getAppID().equals("12345")),
				() -> assertTrue(app.getApp("12345").getDate().equals(new Date(1742486400000L))),
				() -> assertTrue(app.getApp("12345").getDesc().equals("New Description for Test")));
		}
		

}
