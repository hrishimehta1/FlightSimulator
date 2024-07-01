#Flight Path Analysis

**Advanced Flight Path Analysis using C++, Graph Algorithms, and File Processing**

This project includes two programs, `fly.cpp` and `create.cpp`, that work together to analyze and manipulate flight route data. The project provides functionality to find the shortest or least costly paths between airports, and to condense large datasets for easier handling.

## Features

- **Graph Representation**: Uses both adjacency lists and adjacency matrices to represent flight routes.
- **Path Finding**: Implements Dijkstra's algorithm to find the shortest or least costly paths between airports.
- **File Processing**: Reads flight data from a CSV file and initializes the graph.
- **Condensed Data Output**: Creates a condensed version of the flight data file, storing every 10th line.

## File Descriptions

### `fly.cpp`

- **Graph Class**:
  - `insertEdgeAL`: Adds an edge to the adjacency list if it doesn't already exist.
  - `isEdge` and `isEdgeAM`: Check if an edge exists in the adjacency list and adjacency matrix, respectively.
  - `getAdjacent`: Returns the adjacent vertices for a given vertex.
  - `shortestPath`: Uses Dijkstra's algorithm on the adjacency list to find the shortest or least costly path.
  - `dijkstraAM`: Uses Dijkstra's algorithm on the adjacency matrix to find the shortest or least costly path.
  - `readFile`: Reads flight data from a file and initializes both the adjacency list and matrix.
  - `printGraphAL`, `printGraphAM`, `printLocations`, `displayOptions`: Helper functions to print the graph and locations for debugging.
  - `findLocation`, `findLocationAM`: Find the string representation of a location given its index.

- **Main Function**:
  - Reads the filename from the user.
  - Initializes two graphs: one for cost and one for distance.
  - Reads the file and populates the graphs.
  - Provides a menu for the user to choose between finding the least costly path or the shortest path.
  - Allows the user to enter the origin and destination airports.
  - Prints the result of the chosen path-finding algorithm.
  - Measures and prints the time taken for various operations.

### `create.cpp`

- **writeFile**:
  - Reads the flight data from `flights.csv`.
  - Stores every 10th line from the original file in a vector.
  - Writes the condensed data to `flightsv4.csv`.

## How to Compile and Run

### Compiling

To compile the programs, use the following commands:

```bash
g++ -o fly fly.cpp
g++ -o create create.cpp


## Running the Programs

### Running `fly`

To run the `fly` program:

```bash
./fly
```

### Running `create`

To run the `create` program:

```bash
./create
```

## Example Usage

### `fly.cpp`

- Compile and run the `fly` program.
- Enter the flight data file name when prompted.
- Choose whether to find the least costly path or the shortest path.
- Enter the origin and destination airports.
- View the results, including the path and the total cost or distance.

### `create.cpp`

- Compile and run the `create` program.
- The program will read `flights.csv`, condense the data, and write it to `flightsv4.csv`.

## Future Enhancements

- Enhance User Interface: Add a graphical user interface (GUI) for better visualization and interaction.
- Additional Algorithms: Implement other path-finding algorithms like A* or Bellman-Ford.
- Real-Time Data: Integrate real-time data from APIs to keep the flight information up to date.
- Performance Optimization: Improve the efficiency of the graph data structures and algorithms.
- Error Handling: Add robust error handling to manage issues with the input data.

## Contributing

Contributions are welcome! Please feel free to submit a pull request or open an issue to discuss improvements or report bugs.

## License

This project is licensed under the MIT License.


Enjoy using the Flight Path Analysis project!
