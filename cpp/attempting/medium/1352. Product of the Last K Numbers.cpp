
#include<vector>

class ProductOfNumbers 
{
private:
    vector<int*> products; // store the products based on what was added to the stream
public:
    ProductOfNumbers() : products({})
    {
    }
    
    void add(int num) 
    {
        /*
        Idea for storing stream and how to quickly compute the last `z` products quickly:
        ex.
        stream = []
        products = []
        
        add 10
        stream = [10]
        products = [10] // k = 1 return 10
        
        add 2
        stream = [10, 2]
        products = [2, 20]              // [20, 2]    
            products[0] is for k = 1,
            products[1] is for k = 2
        
        add 1
        stream = [10, 2, 1]
        products = [1, 2, 20]

        add 2
        stream = [10, 2, 1, 2]
        products = [2, 2, 4, 40]

        add 5
        stream = [10,2,1,2,5]
        products = [5,10,10,20,200]

        We can also represent `products` this way:
        products = [200, 20, 10, 10, 5], then
            [0] is for k = products.size(), k = 5
            [1] is for k = 4
            [2] is for k = 3
            [3] is for k = 2
            [4] is for k = 1
            we need to products.size() - k to get the right index.
        */
        
        if (products.size() == 0)
        {
            products.push_back(new int(num));
            return;
        }

        // update the products we've calculated so far with `num`
        for (int* productPtr : products)
        {
            (*productPtr) *= num;
        }

        products.push_back(new int(num));
    }
    
    int getProduct(int k) 
    {
        cout << "[";
        for (int* ptr : products)
        {
            cout << *ptr << ", ";
        }
        cout << "]" << endl;

        return *products[products.size() - k];
    }
};

/**
 * Your ProductOfNumbers object will be instantiated and called as such:
 * ProductOfNumbers* obj = new ProductOfNumbers();
 * obj->add(num);
 * int param_2 = obj->getProduct(k);
 */