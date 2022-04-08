Maze::Maze(std::string fileName) 
{
    std::string rawText = ""; // emtpy string to hold .txt file content 
    std::string lineIn = "";
    std::ifstream inFile;
    mRow = 0;
    mCol = 0;

    inFile.open(fileName.c_str());

    if (inFile.is_open()) { // Reading .txt file
        std::cout << "The file has been read" << std::endl << std::endl;
        while (!inFile.eof()) {
            std::getline(inFile, lineIn);
            rawText += lineIn;
            mRow++;
        }

        mCol = lineIn.length();
        cMatrix = std::vector<std::vector<Cell*>>(mRow, std::vector<Cell*>(mCol, nullptr)); // creating a 2d vector to hold the maze text file 
        int row = 0;
        int col = 0;

        for (int i = 0; i < rawText.size(); i++) {
            if (!(rawText[i] == ' ' || rawText[i] == 'S' || rawText[i] == 'E')) {
                continue;
            }
            if (mCol > 0) {
                row = i / mCol;
                col = i % mCol;
            }
            if (cMatrix[row][col] == nullptr) {
                cMatrix[row][col] = new Cell();
            }
            if (rawText[i] == 'S') {
                mStart = cMatrix[row][col];
            }
            if (rawText[i] == 'E') {
                cMatrix[row][col]->mIsExit = true;
            }
        }

        for (row = 0; row < mRow; row++) { // Link nodes and print nodes to console
         
            for (col = 0; col < mCol; col++) {
            
                if (cMatrix[row][col] == nullptr) {
                    std::cout << "X";
                    continue;
                }
                else if (cMatrix[row][col] -> mIsExit) {
                    std::cout << "E";
                }
                else {
                    std::cout << " ";
                }

                if (row - 1 >= 0 && cMatrix[row - 1][col] != nullptr) { // North in bounds
                
                    cMatrix[row][col] -> mNorth = cMatrix[row - 1][col];
                }
                if (row + 1 < mRow && cMatrix[row + 1][col] != nullptr) { // South in bounds
                
                    cMatrix[row][col] -> mSouth = cMatrix[row + 1][col];
                }
                if (col + 1 < mCol && cMatrix[row][col + 1] != nullptr) { // East in bounds

                    cMatrix[row][col] -> mEast = cMatrix[row][col + 1];
                }
                if (col - 1 >= 0 && cMatrix[row][col - 1] != nullptr) { // West in bounds
                
                    cMatrix[row][col] -> mWest = cMatrix[row][col - 1];
                }
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;

    }
    else {
        std::cout << "The file cannot be opened." << std::endl;
        inFile.close();
    }
 }