package main;

import java.util.HashMap;

public class TaskService {
	private HashMap<String, Task> service = new HashMap<String, Task>();
	
	/**
	 * @param Add Task to Task Service using ID, name, and description
	 */
	public void AddTask(String ID, String name, String desc) {
		//check ID before setting it
		if (ID == null || ID.length() > 10 || ID.isEmpty()) {
			throw new IllegalArgumentException("Invalid ID");
		}
		
		//create new Task Object and input into HashMap service
		service.put(ID, new Task(ID, name, desc));
	}
	
	/**
	 * @param delete Task based on given ID
	 * @return true if removed
	 */
	public void DeleteTask(String ID) {
		//if ID is found, removes task
		service.remove(ID);
	}
	
	/**
	 * @param update name and description using ID
	 */
	public void UpdateTask(String ID, String name, String desc) {
		service.get(ID).setName(name);
		service.get(ID).setDescription(desc);
	}
	
	/**
	 * @param update name using ID
	 */
	public void UpdateTaskName(String ID, String name) {
		service.get(ID).setName(name);
	}
	
	/**
	 * @param update description using ID
	 */
	public void UpdateTaskDescription(String ID, String desc) {
		service.get(ID).setDescription(desc);
	}
	
	/**
	 * @return Task based on given ID
	 */
	public Task getTask(String ID) {
		return service.get(ID);
	}
}
