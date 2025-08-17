package main;

import java.util.Date;
import java.util.HashMap;

public class AppointmentService {
	
	private HashMap<String, Appointment> appService = new HashMap<String, Appointment>();
	
	/**
	 * @param Add Appointment to Appointment Service using ID, date, and description
	 */
	public void AddAppointment(String ID, Date date, String desc) {
		//check ID before setting it
		if (ID == null || ID.length() > 10 || ID.isEmpty()) {
			throw new IllegalArgumentException("Invalid ID");
		}
		
		//create new Appointment Object and input into HashMap service
		appService.put(ID, new Appointment(ID, date, desc));
	}
	
	/**
	 * @param delete Appointment based on given ID
	 */
	public void DeleteAppointment(String ID) {
		appService.remove(ID);
	}
	
	/**
	 * @param update date and description using ID
	 */
	public void UpdateAppointment(String ID, Date date, String desc) {
		appService.get(ID).setDate(date);
		appService.get(ID).setDesc(desc);
	}
	
	/**
	 * @return appointment based on given ID
	 */
	public Appointment getApp(String ID) {
		return appService.get(ID);
	}
}
