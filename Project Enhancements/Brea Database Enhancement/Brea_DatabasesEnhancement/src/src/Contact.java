package src;

public class Contact {
	private final String iD;
	private String firstName;
	private String lastName;
	private String phone;
	private String address;
	
	public Contact(String iD, String firstName, String lastName, String phone, String address) {
		
		//checks if iD is null, more than 10 characters, or empty
		if (iD == null || iD.length() > 10 || iD.isEmpty()) {
			throw new IllegalArgumentException("Invalid ID");
		}
		
		//checks if firstName is null, more than 10 characters, or empty
		if (firstName == null || firstName.length() > 10 || firstName.isEmpty()) {
			throw new IllegalArgumentException("Invalid First Name");
		}
		
		//checks if lastName is null, more than 10 characters, or empty
		if (lastName == null || lastName.length() > 10 || lastName.isEmpty()) {
			throw new IllegalArgumentException("Invalid Last Name");
		}
		
		//checks if phone is null, not 10 characters, or empty
		if (phone == null || phone.length() != 10 || phone.isEmpty()) {
			throw new IllegalArgumentException("Invalid Phone Number");
		}
		
		//checks if address is null, more than 30 characters, or empty
		if (address == null || address.length() > 30 || address.isEmpty()) {
			throw new IllegalArgumentException("Invalid Address");
		}
		
		//set all if nothing thrown
		this.iD = iD;
		this.firstName = firstName;
		this.lastName = lastName;
		this.phone = phone;
		this.address = address;
	}

	//return firstName
	public String getFirstName() {
		return firstName;
	}

	//set firstName if within boundaries
	public void setFirstName(String firstName) {
		if (firstName == null || firstName.length() > 10 || firstName.isEmpty()) {
			throw new IllegalArgumentException("Invalid First Name");
		}
		
		this.firstName = firstName;
	}

	//return lastName
	public String getLastName() {
		return lastName;
	}

	//set lastName if within boundaries
	public void setLastName(String lastName) {
		if (lastName == null || lastName.length() > 10 || lastName.isEmpty()) {
			throw new IllegalArgumentException("Invalid Last Name");
		}
		
		this.lastName = lastName;
	}

	//return phone
	public String getPhone() {
		return phone;
	}

	//set phone if within boundaries
	public void setPhone(String phone) {
		if (phone == null || phone.length() != 10 || phone.isEmpty()) {
			throw new IllegalArgumentException("Invalid Phone Number");
		}
		
		this.phone = phone;
	}

	//return address
	public String getAddress() {
		return address;
	}

	//set address if within boundaries
	public void setAddress(String address) {
		if (address == null || address.length() > 30 || address.isEmpty()) {
			throw new IllegalArgumentException("Invalid Address");
		}
		
		this.address = address;
	}

	public String getiD() {
		return iD;
	}
	
	
}
