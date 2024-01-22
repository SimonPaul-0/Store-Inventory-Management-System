#include <iostream>
#include <vector>
#include <algorithm>

class Product {
public:
    Product(int id, std::string name, double price, int quantity) 
        : id(id), name(std::move(name)), price(price), quantity(quantity) {}

    int getId() const { return id; }
    std::string getName() const { return name; }
    double getPrice() const { return price; }
    int getQuantity() const { return quantity; }

    void displayDetails() const {
        std::cout << "Product ID: " << id << "\n"
                  << "Name: " << name << "\n"
                  << "Price: $" << price << "\n"
                  << "Quantity: " << quantity << "\n\n";
    }

private:
    int id;
    std::string name;
    double price;
    int quantity;
};

class Inventory {
public:
    void addProduct(const Product& product) {
        products.push_back(product);
        std::cout << "Product added to the inventory.\n\n";
    }

    void displayInventory() const {
        if (products.empty()) {
            std::cout << "Inventory is empty.\n\n";
        } else {
            std::cout << "Current Inventory:\n";
            for (const auto& product : products) {
                product.displayDetails();
            }
        }
    }

    void sellProduct(int productId, int quantity) {
        auto it = std::find_if(products.begin(), products.end(),
                               [productId](const Product& p) { return p.getId() == productId; });

        if (it != products.end()) {
            if (it->getQuantity() >= quantity) {
                it->displayDetails();
                std::cout << "Selling " << quantity << " units.\n"
                          << "Total Cost: $" << (it->getPrice() * quantity) << "\n\n";
                it->getQuantity() -= quantity;
                if (it->getQuantity() == 0) {
                    products.erase(it);
                    std::cout << "Product removed from the inventory.\n\n";
                }
            } else {
                std::cout << "Not enough quantity available for the sale.\n\n";
            }
        } else {
            std::cout << "Product not found in the inventory.\n\n";
        }
    }

private:
    std::vector<Product> products;
};

int main() {
    Inventory storeInventory;

    Product product1(1, "Laptop", 1200.0, 10);
    Product product2(2, "Smartphone", 800.0, 15);
    Product product3(3, "Headphones", 50.0, 30);

    storeInventory.addProduct(product1);
    storeInventory.addProduct(product2);
    storeInventory.addProduct(product3);

    storeInventory.displayInventory();

    storeInventory.sellProduct(2, 3);
    storeInventory.sellProduct(1, 5);

    storeInventory.displayInventory();

    return 0;
}
