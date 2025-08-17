package test;

import static org.junit.jupiter.api.Assertions.*;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;

import src.Task;

class TaskTest {

	@Test
	void testTaskClass() {
		Task taskClass = new Task("12345", "Task Name", "This is the description for the task");
		assertAll("Should initialize all variables of task",
				() -> assertTrue(taskClass.getID().equals("12345")),
				() -> assertTrue(taskClass.getName().equals("Task Name")),
				() -> assertTrue(taskClass.getDescription().equals("This is the description for the task")));
	}
	
	@Test
	void testTaskClassSetters() {
		Task taskClass = new Task("12345", "Task Name", "This is the description for the task");
		taskClass.setName("New Task Name");
		taskClass.setDescription("New description");
		assertAll("Should set name and description to new strings in task",
				() -> assertTrue(taskClass.getName().equals("New Task Name")),
				() -> assertTrue(taskClass.getDescription().equals("New description")));
	}
	
	@Test
	void testSettersNull() {
		Task taskClass = new Task("12345", "Task Name", "This is the description for the task");
		assertAll("Should all throw illegal argument exception",
				() -> assertThrows(IllegalArgumentException.class, () -> taskClass.setName(null)),
				() -> assertThrows(IllegalArgumentException.class, () -> taskClass.setDescription(null)));
				
	}
	
	@Test
	void testTaskIDTooLong() {
		Assertions.assertThrows(IllegalArgumentException.class, () -> {
			new Task("12345678901", "Task Name", "This is the description for the task");
		});
	}
	
	@Test
	void testTaskIDNull() {
		Assertions.assertThrows(IllegalArgumentException.class, () -> {
			new Task(null, "Task Name", "This is the description for the task");
		});
	}
	
	@Test
	void testTaskIDisEmpty() {
		Assertions.assertThrows(IllegalArgumentException.class, () -> {
			new Task("", "Task Name", "This is the description for the task");
		});
	}
	
	@Test
	void testTaskNameTooLong() {
		Assertions.assertThrows(IllegalArgumentException.class, () -> {
			new Task("12345", "Way Too Long of A Task Name For This Test", "This is the description for the task");
		});
	}
	
	@Test
	void testTaskNameisNull() {
		Assertions.assertThrows(IllegalArgumentException.class, () -> {
			new Task("12345", null, "This is the description for the task");
		});
	}
	
	@Test
	void testTaskNameisEmpty() {
		Assertions.assertThrows(IllegalArgumentException.class, () -> {
			new Task("12345", "", "This is the description for the task");
		});
	}

	@Test
	void testTaskDescTooLong() {
		Assertions.assertThrows(IllegalArgumentException.class, () -> {
			new Task("12345", "Task Name", "This is the description for the task way too long for the current test about the description past the fifty character limit");
		});
	}
	
	@Test
	void testTaskDescisNull() {
		Assertions.assertThrows(IllegalArgumentException.class, () -> {
			new Task("12345", "Task Name", null);
		});
	}
	
	@Test
	void testTaskDescisEmpty() {
		Assertions.assertThrows(IllegalArgumentException.class, () -> {
			new Task("12345", "Task Name", "");
		});
	}
	
}
