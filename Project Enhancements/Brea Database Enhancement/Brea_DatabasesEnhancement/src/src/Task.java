package src;

public class Task {

	private final String ID;
	private String name;
	private String desc;
	
	/**
	 * @param iD
	 * @param name
	 * @param description
	 */
	public Task(String ID, String name, String desc) {
		//checks if ID is null, more than 10 characters, or empty
		if (ID == null || ID.length() > 10 || ID.isEmpty()) {
			throw new IllegalArgumentException("Invalid ID");
		}
		
		//checks if Name is null, more than 20 characters, or empty
		if (name == null || name.length() > 20 || name.isEmpty()) {
			throw new IllegalArgumentException("Invalid Name");
		}
		
		//checks if Description is null, more than 50 characters, or empty
		if (desc == null || desc.length() > 50 || desc.isEmpty()) {
			throw new IllegalArgumentException("Invalid Description");
		}
		
		//set all if nothing thrown
		this.ID = ID;
		this.name = name;
		this.desc = desc;
	}
	
	/**
	 * @return the name
	 */
	public String getName() {
		return name;
	}
	
	/**
	 * @param name the name to set
	 */
	public void setName(String name) {
		if (name == null || name.length() > 20 || name.isEmpty()) {
			throw new IllegalArgumentException("Invalid Name");
		}
		
		this.name = name;
	}
	
	/**
	 * @return the description
	 */
	public String getDescription() {
		return desc;
	}
	
	/**
	 * @param description the description to set
	 */
	public void setDescription(String desc) {
		if (desc == null || desc.length() > 50 || desc.isEmpty()) {
			throw new IllegalArgumentException("Invalid Description");
		}
		
		this.desc = desc;
	}
	
	/**
	 * @return the iD
	 */
	public String getID() {
		return ID;
	}
	
	
}
