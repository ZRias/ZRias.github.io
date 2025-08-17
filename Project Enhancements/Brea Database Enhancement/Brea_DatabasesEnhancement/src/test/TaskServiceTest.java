package test;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

import src.TaskService;

class TaskServiceTest extends BaseTest {

	@Test
	void testTaskServiceAddTask() {
		TaskService Tasks = new TaskService();
		
		Tasks.addTask("12345", "Task Name", "This is the description for the task");
		assertAll("Should add task to Tasks with no errors",
				() -> assertTrue(Tasks.getTask("12345").getID().equals("12345")),
				() -> assertTrue(Tasks.getTask("12345").getName().equals("Task Name")),
				() -> assertTrue(Tasks.getTask("12345").getDescription().equals("This is the description for the task")));
	}
	
	@Test
	void testTaskServiceDeleteTask() {
		TaskService Tasks = new TaskService();
		
		Tasks.addTask("12345", "Task Name", "This is the description for the task");
		
		Tasks.deleteTask("12345");
		
		assertThrows(NullPointerException.class, () -> {
			Tasks.getTask("12345").getID().equals("12345");
		});
	}

	@Test
	void testUpdateTask() {
		TaskService Tasks = new TaskService();
		
		Tasks.addTask("12345", "Task Name", "This is the description for the task");
		Tasks.updateTask("12345", "NEW Task Name", "This is the NEW description for the task");
		assertAll("Should update task in Tasks with no errors",
			() -> assertTrue(Tasks.getTask("12345").getName().equals("NEW Task Name")),
			() -> assertTrue(Tasks.getTask("12345").getDescription().equals("This is the NEW description for the task")));
	}
	
	@Test
	void testUpdateTaskName() {
		TaskService Tasks = new TaskService();
		
		Tasks.addTask("12345", "Task Name", "This is the description for the task");
		Tasks.updateTaskName("12345", "NEW Task Name");
		
		assertTrue(Tasks.getTask("12345").getName().equals("NEW Task Name"));
	}
	
	@Test
	void testUpdateTaskDesc() {
		TaskService Tasks = new TaskService();
		
		Tasks.addTask("12345", "Task Name", "This is the description for the task");
		Tasks.updateTaskDescription("12345", "This is the NEW description for the task");
		
		assertTrue(Tasks.getTask("12345").getDescription().equals("This is the NEW description for the task"));
	}
	
	@Test
	void testIDNull() {
		TaskService Tasks = new TaskService();
		
		assertThrows(IllegalArgumentException.class, () -> {
			Tasks.addTask(null, "Task Name", "This is the description for the task");
		});
	}
	
	@Test
	void testIDEmpty() {
		TaskService Tasks = new TaskService();
		
		assertThrows(IllegalArgumentException.class, () -> {
			Tasks.addTask("", "Task Name", "This is the description for the task");
		});
	}
	
}
