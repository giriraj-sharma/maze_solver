#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

// Define grid dimensions
const int ROW = 5;
const int COL = 5;

// Directions for moving in the grid: Up, Down, Left, Right
int rowDir[] = {-1, 1, 0, 0};
int colDir[] = {0, 0, -1, 1};

// Function to check if a cell is valid to move to 
// (Must be within boundaries, not an obstacle, and not previously visited)
bool isValid(int row, int col, const vector<vector<int>>& grid, const vector<vector<bool>>& visited) {
    return (row >= 0) && (row < ROW) && 
           (col >= 0) && (col < COL) && 
           (grid[row][col] == 0) && 
           (!visited[row][col]);
}

// Function to find the shortest path using Breadth-First Search (BFS)
void solveMazeBFS(vector<vector<int>>& grid, pair<int, int> start, pair<int, int> destination) {
    // 2D array to keep track of visited cells to prevent infinite loops
    vector<vector<bool>> visited(ROW, vector<bool>(COL, false));
    
    // 2D array to store the parent of each cell for optimal path reconstruction
    vector<vector<pair<int, int>>> parent(ROW, vector<pair<int, int>>(COL, {-1, -1}));
    
    // Queue to handle BFS traversal
    queue<pair<int, int>> q;
    
    // Start from the source node
    q.push(start);
    visited[start.first][start.second] = true;
    
    bool reached = false;
    
    while (!q.empty()) {
        pair<int, int> curr = q.front();
        q.pop();
        
        int currRow = curr.first;
        int currCol = curr.second;
        
        // Base case: Check if we reached the destination
        if (currRow == destination.first && currCol == destination.second) {
            reached = true;
            break;
        }
        
        // Explore all 4 possible directions from current cell
        for (int i = 0; i < 4; i++) {
            int newRow = currRow + rowDir[i];
            int newCol = currCol + colDir[i];
            
            if (isValid(newRow, newCol, grid, visited)) {
                visited[newRow][newCol] = true;
                parent[newRow][newCol] = {currRow, currCol}; // Track the path
                q.push({newRow, newCol});
            }
        }
    }
    
    // Output the result
    if (reached) {
        cout << "Path found! Reconstructing the optimal path...\n";
        
        // Reconstruct path using a stack to print from start to destination
        stack<pair<int, int>> path;
        pair<int, int> step = destination;
        
        while (step.first != -1 && step.second != -1) {
            path.push(step);
            step = parent[step.first][step.second];
        }
        
        // Print the path sequence
        cout << "Start -> ";
        while (!path.empty()) {
            pair<int, int> node = path.top();
            path.pop();
            cout << "(" << node.first << ", " << node.second << ")";
            if (!path.empty()) cout << " -> ";
        }
        cout << " -> Destination\n";
    } else {
        // Edge case handling: Unreachable path
        cout << "No path found! The destination is unreachable due to obstacles.\n";
    }
}

int main() {
    // Grid representation: 
    // 0 = Open path
    // 1 = Obstacle (Wall)
    vector<vector<int>> maze = {
        {0, 1, 0, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 0, 1, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 0, 0, 0}
    };
    
    pair<int, int> start = {0, 0};
    pair<int, int> destination = {4, 4};
    
    cout << "--- Maze Solver Initialization ---\n";
    cout << "Start Coordinates: (0, 0)\n";
    cout << "Destination Coordinates: (4, 4)\n\n";
    
    solveMazeBFS(maze, start, destination);
    
    return 0;
}
