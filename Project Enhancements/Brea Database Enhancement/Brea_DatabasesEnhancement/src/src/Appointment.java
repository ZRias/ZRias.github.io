package src;

import java.util.Date;
import java.time.LocalDate;

public class Appointment {
	private final String appID;
	private Date date;
	private String desc;
	
	/**
	 * @param appID
	 * @param date
	 * @param desc
	 */
	public Appointment(String appID, Date date, String desc) {
		if (appID == null || appID.length() > 10 || appID.isEmpty()) {
			throw new IllegalArgumentException("Invalid ID");
		}
		if (date == null || date.before(new Date())) {
			throw new IllegalArgumentException("Invalid Date");
		}
		if (desc == null || desc.length() > 50 || desc.isEmpty()) {
			throw new IllegalArgumentException("Invalid Description");
		}
		
		
		this.appID = appID;
		this.date = date;
		this.desc = desc;
	}

	/**
	 * @return the date
	 */
	public Date getDate() {
		return date;
	}

	/**
	 * @param date the date to set
	 */
	public void setDate(Date date) {
		if (date == null || date.before(new Date())) {
			throw new IllegalArgumentException("Invalid Date");
		}
		
		this.date = date;
	}

	/**
	 * @return the desc
	 */
	public String getDesc() {
		
		return desc;
	}

	/**
	 * @param desc the desc to set
	 */
	public void setDesc(String desc) {
		if (desc == null || desc.length() > 50 || desc.isEmpty()) {
			throw new IllegalArgumentException("Invalid Description");
		}
		
		this.desc = desc;
	}

	/**
	 * @return the appID
	 */
	public String getAppID() {
		return appID;
	}
	
	
	
}
