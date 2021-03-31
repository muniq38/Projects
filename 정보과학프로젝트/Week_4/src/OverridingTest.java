
class Employee {
	int age;
	String name; // Class Manager까지만 접근할 수 있게
	
	public Employee(String name, int age) {
		this.age = age;
		this.name = name;
	}
	
	public Employee(Employee A) {
		this.age = A.age;
		this.name = A.name;
	}

	public int getAge() { return age; }
	public String getName() { return name; }
	
	public void print(){ 
		System.out.println("* 사원의 이름은 "+name+"이고, 나이는 "+age+"입니다.");
	}
}

class Manager extends Employee {
	String JobOfManager;
	
	public Manager(String name, int age, String Job) {
		super(name,age);
		this.JobOfManager = Job;
	}
	
	public Manager(Employee A, String Job) {
		super(A);
		this.JobOfManager = Job;
	}
	
	public String getJob() { return JobOfManager; }
	
	public void Print() {
		System.out.println("- 관리자 "+name+"의 직함은 "+JobOfManager+"입니다."); 
	}
}
 

public class OverridingTest {
	public OverridingTest() { }
	public static void main(String[] args) {
		Employee E1 = new Employee("Kim min",25);
		Employee E2 = new Employee("Lee Joon",30);
		E1.print(); E2.print();
		Manager M1 = new Manager(E2, "Project Manager");
		M1.Print();
	}
}
