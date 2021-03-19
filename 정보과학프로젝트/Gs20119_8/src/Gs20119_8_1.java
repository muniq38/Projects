
class Product{
	String name = "물"; 
	int price = 800;
	
	Product(String name, int price){ 
		this.name=name; this.price=price; 
	}Product(String name){ this.name=name; }
	Product(int price){ this.price=price; }
	Product(){ }
	
	String getName() { return name; }
	int getPrice() { return price; }
	
	void setName(String name) { this.name=name; }
	void setPrice(int price) { this.price=price; }
}

class ProductTest{
	ProductTest(){ }
	static void main(String args[]) {
		for(int i=0; i<4; i++) {
			Product p = Gs20119_8_1.P[i];
			System.out.println(p.name+", "+p.price);
		}
	}
}

public class Gs20119_8_1 {
	static Product[] P = new Product[4];
	public static void main(String args[]) {
		P[0] = new Product("웰치스",700);
		P[1] = new Product("커피");
		P[2] = new Product(500);
		P[3] = new Product();	
		ProductTest.main(args);
	}
}

