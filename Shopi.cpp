#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <unordered_map>

class Product
{
public:
    int id;
    std::string name;
    double price;

    Product(int id, std::string name, double price)
        : id(id), name(name), price(price) {}

    // Add a default constructor
    Product() : id(0), name(""), price(0.0) {}
};

class ShoppingCart
{
public:
    std::vector<Product> items;

    void addProduct(const Product &product)
    {
        items.push_back(product);
    }

    double calculateTotal()
    {
        return std::accumulate(items.begin(), items.end(), 0.0,
                               [](double sum, const Product &product)
                               {
                                   return sum + product.price;
                               });
    }

    void displayCart()
    {
        if (items.empty())
        {
            std::cout << "Your cart is empty.\n";
            return;
        }

        std::cout << "Items in Cart:\n";
        for (const Product &product : items)
        {
            std::cout << "- " << product.name << " - $" << product.price << "\n";
        }
        std::cout << "Total: $" << calculateTotal() << "\n";
    }
};

class ProductCatalog
{
private:
    std::unordered_map<int, Product> productMap;

public:
    void addProduct(const Product &product)
    {
        productMap[product.id] = product;
    }

    Product getProduct(int id)
    {
        auto it = productMap.find(id);
        if (it != productMap.end())
        {
            return it->second;
        }
        else
        {
            return Product(0, "Invalid Product", 0.0);
        }
    }

    void listProducts()
    {
        std::cout << "Available Products:\n";
        for (const auto &entry : productMap)
        {
            const Product &product = entry.second;
            std::cout << product.id << ". " << product.name << " - $" << product.price << "\n";
        }
    }
};

int main()
{
    ProductCatalog catalog;
    catalog.addProduct(Product(1, "Laptop", 1000.0));
    catalog.addProduct(Product(2, "Phone", 500.0));
    catalog.addProduct(Product(3, "T-shirt", 20.0));

    ShoppingCart cart;

    while (true)
    {
        std::cout << "\n=== Online Shopping System ===\n";
        std::cout << "1. View Products\n";
        std::cout << "2. Add to Cart\n";
        std::cout << "3. View Cart\n";
        std::cout << "4. Checkout\n";
        std::cout << "5. Exit\n";
        int choice;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            catalog.listProducts();
            break;
        case 2:
        {
            int productId;
            std::cout << "Enter product ID to add to cart: ";
            std::cin >> productId;
            Product product = catalog.getProduct(productId);
            if (product.id != 0)
            {
                cart.addProduct(product);
                std::cout << product.name << " added to cart.\n";
            }
            else
            {
                std::cout << "Invalid product ID.\n";
            }
            break;
        }
        case 3:
            cart.displayCart();
            break;
        case 4:
            if (!cart.items.empty())
            {
                std::cout << "Checkout completed. Thank you for shopping!\n";
                return 0;
            }
            else
            {
                std::cout << "Your cart is empty. Add items before checking out.\n";
            }
            break;
        case 5:
            std::cout << "Exiting the Online Shopping System.\n";
            return 0;
        default:
            std::cout << "Invalid choice. Please select a valid option.\n";
        }
    }

    return 0;
}
