#pragma once
#include <vector>
#include <string>

struct Node {
    double x, y, z; // Coordinates of the node
};

struct Element {
    std::vector<int> nodeIDs; // Indices of the nodes forming the element
};

struct BoundaryPatch {
    std::string name;           // Name of the patch (e.g., "inlet", "outlet")
    std::string type;           // Type of the patch (e.g., "patch", "wall")
    int nFaces;                 // Number of faces in this boundary patch
    int startFace;              // Index of the first face in the patch
    std::vector<int> faceIDs;   // Indices of the faces associated with this boundary patch
};

class Grid {
    public:
        Grid();
        bool loadMesh(const std::string& filePath); // Load mesh from fluent or OpenFOAM
        const std::vector<Node>& getNodes() const;
        const std::vector<Element>& getElements() const;
        const std::vector<BoundaryPatch>& getBoundaryPatches() const;
        const std::vector<int>& getNeighbours() const;
        const std::vector<int>& getOwners() const;

    private:
        std::vector<Node> nodes_;                    // List of nodes (points)
        std::vector<Element> elements_;              // List of elements (faces)
        std::vector<BoundaryPatch> boundaryPatches_; // Boundary patches information
        std::vector<int> neighbours_;                // Neighboring face IDs
        std::vector<int> owners_;                    // Owner face IDs

        bool parseMSHFile(const std::string& filePath);
        bool parseFOAMMesh(const std::string& dirPath);
};
