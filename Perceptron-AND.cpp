#include <iostream>
#include <vector>
#include <cstdlib> // Para la generación de números aleatorios

// Función de activación (función escalón)
int step_function(double x) {
    return x >= 0 ? 1 : 0;
}

// Función de entrenamiento del perceptrón
void trainPerceptron(std::vector<std::vector<double>> &inputs, std::vector<int> &targetOutput, double learningRate, int maxIterations) {
    // Inicialización de pesos y sesgo de manera aleatoria
    std::vector<double> weights(inputs[0].size());
    for (int i = 0; i < inputs[0].size(); ++i) {
        weights[i] = ((double)rand() / RAND_MAX) * 2 - 1; // Valores aleatorios en el rango [-1, 1]
    }
    double bias = ((double)rand() / RAND_MAX) * 2 - 1;
    int iteration = 0;

    while (iteration < maxIterations) {
        int errorCount = 0;

        for (int i = 0; i < inputs.size(); ++i) {
            std::vector<double> inputVector = inputs[i];
            int target = targetOutput[i];
            
            // Calcular la salida del perceptrón
            double output = 0;
            for (int j = 0; j < inputVector.size(); ++j) {
                output += weights[j] * inputVector[j];
            }
            output += bias;
            int prediction = step_function(output);

            // Calcular el error
            int error = target - prediction;

            // Actualizar pesos y sesgo si es necesario
            if (error != 0) {
                for (int j = 0; j < weights.size(); ++j) {
                    weights[j] += learningRate * error * inputVector[j];
                }
                bias += learningRate * error;
                errorCount++;
            }

            // Mostrar entrada, salida, y error
            std::cout << "Entrada: [";
            for (int j = 0; j < inputVector.size(); ++j) {
                std::cout << inputVector[j];
                if (j < inputVector.size() - 1) {
                    std::cout << ", ";
                }
            }
            std::cout << "], Salida Esperada: " << target << ", Salida del Perceptrón: " << prediction << ", Error: " << error << std::endl;
        }

        iteration++;

        // Si no se comete ningún error, el perceptrón ha aprendido la función
        if (errorCount == 0) {
            break;
        }
    }
}

int main() {
    // Datos de entrada para la compuerta lógica AND
    std::vector<std::vector<double>> inputs = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
    std::vector<int> targetOutput = {0, 0, 0, 1};

    // Entrenar el perceptrón
    trainPerceptron(inputs, targetOutput, 0.1, 1000);

    return 0;
}
