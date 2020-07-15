#include <iostream>
#include <vector> 
#include <string>
#include <algorithm>
#define RESET   "\033[0m"
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */

using namespace std;

string vectostr(vector<double> vec)
{
    string output = "{";
    int len = vec.size();
    for (int i = 0; i < len - 1; i++)
    {
        char elem_i[20];
        snprintf(elem_i, 20, "%.2f, ", vec[i]);
        output += elem_i;
    }
    char last_elem[18];
    snprintf(last_elem, 18, "%.2f", vec[vec.size() - 1]);
    output += last_elem;
    output += '}';
    return output;
}

double dot(vector<double>& vec1, vector<double>& vec2)
{
    if (vec1.size() != vec2.size())
    {
        throw("Cannot take dot product of vectors of unequal lengths");
    }
    double total = 0;
    for (int i = 0; i < vec1.size(); i++)
    {
        total += vec1[i] * vec2[i];
    }
    return total;
}

class Sample
{
private:
    vector<double> coords;
    bool is_type_A;
public:
    Sample(vector<double>& coords, bool is_type_A)
    {
        this -> coords = coords;
        this -> is_type_A = is_type_A;
    }
    string tostr() 
    {
    string output = "Sample(";
    output += vectostr(coords);
    output += ", is_type_A: ";
    output += to_string(this -> is_type_A);
    output += ')';
    return output;
    }
    friend ostream& operator<<(ostream& os, Sample& s)
    {
        return os << s.tostr();
    }
    vector<double> get_coords() {return this -> coords;}
    bool get_is_type_A() {return this -> is_type_A;}
};

class Perceptron
{
private:
    vector<Sample> traindata;
    vector<double> weights;
    double bias;
    double lr;  // learning rate
    void initialize_weights()
    {
        weights = {};
        int n_coords = traindata[0].get_coords().size();
        for (int i = 0; i < n_coords; i++)
        {
            weights.push_back(1);
        }
    }
    void initialize_bias()
    {
        bias = 0;
    }
    double calculate_weight_change_multiplier(Sample& sample)
    {
        bool predicted_is_type_A = predict_is_type_A(sample);
        bool actual_is_type_A = sample.get_is_type_A();
        int multiplier = actual_is_type_A - predicted_is_type_A;
        // multiplier: 0 if prediction correct, 
        //            -1 if prediction too big,
        //             1 if prediction too small.
        return multiplier * lr;
    }
    void update_weights_and_bias(Sample& sample)
    {
        double weight_change_multiplier = calculate_weight_change_multiplier(
            sample);
        vector<double> coords = sample.get_coords();
        for (int i = 0; i < coords.size(); i++)
        {
            weights[i] += coords[i] * weight_change_multiplier;
        }
        bias += weight_change_multiplier;
    }
    void train_epoch()
    {
        for (int i = 0; i < traindata.size(); i++) {
            update_weights_and_bias(traindata[i]);
        }
    }
public:
    Perceptron(double& lr, vector<Sample>& traindata)
    {
        this -> lr = lr;
        this -> traindata = traindata;
        initialize_weights();
        initialize_bias();
    }
    string tostr() {
        string output = "Perceptron(weights: ";
        output += vectostr(weights);
        output += ", bias: ";
        char biasstring[20];
        snprintf(biasstring, 20, "%.2f", bias);
        output += biasstring;
        output += ", lr: ";
        char lrstring[20];
        snprintf(lrstring, 20, "%.2f", lr);
        output += lrstring;
        output += ')';
        return output;
    }
    friend ostream& operator<<(ostream& os, Perceptron& p)
    {
        return os << p.tostr();
    }
    bool predict_is_type_A(Sample& sample)
    {
        vector<double> coords = sample.get_coords();
        return dot(weights, coords) + bias > 0;
    }
    void train(int n_epochs = 20, bool reset_params = false)
    {
        if (reset_params)
        {
            initialize_bias();
            initialize_weights();
        }
        for (int i = 0; i < n_epochs; i++)
        {
            train_epoch();
        }
    }
};

Sample get_sample(int dimensions)
{
    vector<double> coords = {};
    for (int i = 0; i < dimensions; i++)
    {
        printf("x_%d: ", i);
        double x_i;
        scanf("%lf", &x_i);
        coords.push_back(x_i);
    }
    bool is_type_A;
    cout << "is_type_A: ";
    cin >> is_type_A;
    return Sample(coords, is_type_A);
}

int main()
{
    int n_samples;
    int n_dims;
    cout << "How many samples? ";
    scanf("%d", &n_samples);
    cout << "How many dimensions? ";
    scanf("%d", &n_dims);
    vector<Sample> traindata = {};
    for (int i = 0; i < n_samples; i++)
    {
        printf("Sample %d\n", i);
        traindata.push_back(get_sample(n_dims));
    }
    double lr;
    cout << "What is the learning rate? ";
    scanf("%lf", &lr);
    Perceptron p = Perceptron(lr, traindata);
    int n_epochs;
    cout << "How many epochs? ";
    scanf("%d", &n_epochs);
    cout << "Before training: " << p << endl;
    p.train(n_epochs);
    cout << ">After training: " << p << endl;
    for (Sample sample_i : traindata)
    {
        cout << "Predicted " << p.predict_is_type_A(sample_i) <<  " for " << sample_i;
        if (p.predict_is_type_A(sample_i) == sample_i.get_is_type_A())
        {
            cout << GREEN << " ✓";
        } else {
           cout << RED << " x"; 
        }
        cout << RESET << endl;
    }
    return 0;
}
