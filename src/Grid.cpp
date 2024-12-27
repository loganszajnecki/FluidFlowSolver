#include "Grid.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

Grid::Grid() = default;

bool Grid::loadMesh(const std::string& filePath) {
    // Identify file type
    if (filePath.substr(filePath.find_last_of('.') + 1) == "msh") {
        return parseMSHFile(filePath);
    } else if (fs::is_directory(filePath)) {
        return parseFOAMMesh(filePath);
    }
    std::cerr << "Unsupported file format or directory: " << filePath << std::endl;
    return false;
}

bool Grid::parseFOAMMesh(const std::string& dirPath) {
    std::string pointsFile    = dirPath + "/points";
    std::string facesFile     = dirPath + "/faces";
    std::string boundaryFile  = dirPath + "/boundary";
    std::string neighbourFile = dirPath + "/neighbour";
    std::string ownerFile     = dirPath + "/owner";

    /**************** Read points file ****************/
    std::ifstream points(pointsFile);
    if (!points.is_open()) {
        std::cerr << "Failed to open points file: " << pointsFile << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(points, line)) {
        // Skip lines with only '(' or ')'
        if (line.find("(") != std::string::npos && line.find(")") == std::string::npos) {
            continue;
        }

        // Remove parentheses from the line
        size_t openParen = line.find("(");
        size_t closeParen = line.find(")");
        if (openParen != std::string::npos && closeParen != std::string::npos) {
            line = line.substr(openParen + 1, closeParen - openParen - 1);
        }

        // Parse the x, y, z coordinates
        double x, y, z;
        std::istringstream iss(line);
        if (iss >> x >> y >> z) {
            nodes_.push_back({x, y, z}); // Correctly store x, y, z
        }
    }
    points.close();

    /**************** Read faces file ************/
    std::ifstream faces(facesFile);
    if (!faces.is_open()) {
        std::cerr << "Failed to open faces file: " << facesFile << std::endl;
        return false;
    }

    while (std::getline(faces, line)) {
        if (line.find("(") != std::string::npos) {
            std::istringstream iss(line);
            std::vector<int> nodeIDs;
            int nodeID;
            while (iss >> nodeID) {
                nodeIDs.push_back(nodeID);
            }
            elements_.push_back({nodeIDs});
        }
    }
    faces.close();

    /**************** Read boundary file ****************/
    std::ifstream boundary(boundaryFile);
    if (!boundary.is_open()) {
        std::cerr << "Failed to open boundary file: " << boundaryFile << std::endl;
        return false;
    }
    while (std::getline(boundary, line)) {
        if (line.find("patch") != std::string::npos || line.find("wall") != std::string::npos 
            || line.find("empty") != std::string::npos) {
            // Skip to the next block after "patch", "wall", or "empty" type declaration
            std::string patchName;
            std::getline(boundary, patchName); // Get the name of the patch (e.g., "inlet")
            
            BoundaryPatch patch;
            patch.name = patchName; // Store the patch name
            
            // Parse the patch details
            while (std::getline(boundary, line) && line.find("}") == std::string::npos) {
                // Extract type, nFaces, startFace
                if (line.find("type") != std::string::npos) {
                    std::istringstream typeStream(line);
                    typeStream >> patch.type;
                }
                if (line.find("nFaces") != std::string::npos) {
                    std::istringstream nFacesStream(line);
                    nFacesStream >> patch.nFaces;
                }
                if (line.find("startFace") != std::string::npos) {
                    std::istringstream startFaceStream(line);
                    startFaceStream >> patch.startFace;
                }
            }

            // Now we know the number of faces and start face, we can store the face indices
            std::vector<int> boundaryFaces;
            for (int i = 0; i < patch.nFaces; ++i) {
                boundaryFaces.push_back(patch.startFace + i); // Store the face indices
            }
            patch.faceIDs = boundaryFaces;

            // Add the patch to the boundaryPatches vector
            boundaryPatches_.push_back(patch);
        }
    }
    boundary.close();

    /**************** Read neighbour file ****************/
    std::ifstream neighbour(neighbourFile);
    if (!neighbour.is_open()) {
        std::cerr << "Failed to open neighbour file: " << neighbourFile << std::endl;
        return false;
    }

    while (std::getline(neighbour, line)) {
        if (line.find("(") != std::string::npos) {
            std::istringstream iss(line);
            int neighborID;
            if (iss >> neighborID) {
                neighbours_.push_back(neighborID); // Store neighbor face ID
            }
        }
    }
    neighbour.close();

    /**************** Read owner file ****************/
    std::ifstream owner(ownerFile);
    if (!owner.is_open()) {
        std::cerr << "Failed to open owner file: " << ownerFile << std::endl;
        return false;
    }

    while (std::getline(owner, line)) {
        if (line.find("(") != std::string::npos) {
            std::istringstream iss(line);
            int ownerID;
            if (iss >> ownerID) {
                owners_.push_back(ownerID); // Store owner face ID
            }
        }
    }
    owner.close();
    return true;
}

bool Grid::parseMSHFile(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filePath << std::endl;
        return false;
    }

    std::string line;
    bool readingNodes = false, readingElements = false;

    while (std::getline(file, line)) {
        if (line.find("$Nodes") != std::string::npos) {
            readingNodes = true;
            continue;
        } else if (line.find("$EndNodes") != std::string::npos) {
            readingNodes = false;
        } else if (line.find("$Elements") != std::string::npos) {
            readingElements = true;
            continue;
        } else if (line.find("$EndElements") != std::string::npos) {
            readingElements = false;
        }

        if (readingNodes) {
            std::istringstream iss(line);
            int id;
            double x, y, z;
            if (iss >> id >> x >> y >> z) {
                nodes_.push_back({x, y});
            }
        }

        if (readingElements) {
            std::istringstream iss(line);
            int id, type, numTags;
            if (iss >> id >> type >> numTags) {
                std::vector<int> tags(numTags);
                for (int& tag : tags) iss >> tag;

                // Read nodes forming the element
                std::vector<int> nodeIDs;
                int nodeID;
                while (iss >> nodeID) {
                    nodeIDs.push_back(nodeID - 1); // Convert to zero-based indexing
                }

                elements_.push_back({nodeIDs});
            }
        }
    }

    file.close();
    return true;
}

const std::vector<Node>& Grid::getNodes() const {
    return nodes_;
}

const std::vector<Element>& Grid::getElements() const {
    return elements_;
}

const std::vector<BoundaryPatch>& Grid::getBoundaryPatches() const {
    return boundaryPatches_;
}

const std::vector<int>& Grid::getNeighbours() const {
    return neighbours_;
}

const std::vector<int>& Grid::getOwners() const {
    return owners_;
}

