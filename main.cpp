#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

// data structure:
// a byte containing 0x02 will sign the start of a block
// the next byte is the amount, the next byte is the character to repeat (no escaping on this byte)

struct block {
    unsigned char sign;
    unsigned char amount;
    unsigned char character;
};

std::string encode(std::string input){
    std::string output;
    for (int i = 0; i < input.size(); i++){


        if (input[i] == 0x02){
            int ii = 0;
            // repeating block start
            // repeat this amount of times
            while (i+ii < input.size() && input[i] == input[i+ii] && ii < 250){
                ii++;
            }
            
            output += 0x02;

            output += output += char(ii);
            // repeat this character
            output += 0x02;
            i+= ii -1;
        }

        // check if 3 or more characters repeat
        else if (i + 3 < input.size() && input[i] == input[i+1] && input[i+1] == input[i+2] && input[i+2] == input[i+3]){

            // get all the characters while they be verbatim
            int ii = 0;
            while (i + ii < input.size() && input[i] == input[i+ii] && ii < 250){
                ii++;
            }
            std::cout << "character" << input[i] << "got repeated" << ii << "times\n";
            // repeating block start
            output += 0x02;
            // times repeated
            output += (char)ii;
            // character to repeat
            output += input[i];

            i += ii -1;

        }


        else {
            output += input[i];
        }
    }
    return output;
}




std::string decode(std::string input){
    std::string output;
    for (int i = 0; i < input.size(); i++){
        if (input[i] == 0x02 && i + 2 < input.size()){
            for (int ii = 0; ii < input[i+1]; ii++){
                output += input[i+2];
            }
            i+= 2;

        }
        else {
            output += input[i];
        }
    }
    return output;
}


int main(int argc, char *argv[]){
    if (argc < 4){
        std::cout << "not enough arguments provided\n" << std::endl;
        return 0;
    }


    char cchar;
    std::string data, result;
    std::ifstream f;
    std::ofstream outfile;

    if (strcmp(argv[1], "c") == 0){



        // read whole file into memory

        f.open(argv[2], std::ios::binary);
        // current charcater to read to
        while (!f.eof()){
            f.read(&cchar, 1);
            data += cchar;
        }
        f.close();
        // remove last char because it's a copy of the char before and will not be useful, reason for this is how we read in the while loop
        data.erase(data.size() -1);

        // we got the whole file data, now we can encode it
        result = encode(data);

        outfile.open(argv[3], std::ios::binary);
        outfile << result;
        outfile.close();
    }
    if (strcmp(argv[1], "d") == 0){


        // read whole file into memory

        f.open(argv[2], std::ios::binary);
        // current charcater to read to
        while (!f.eof()){
            f.read(&cchar, 1);
            data += cchar;
        }
        f.close();
        // remove last char because it's a copy of the char before and will not be useful, reason for this is how we read in the while loop
        data.erase(data.size() -1);

        // we got the whole file data, now we can encode it
        result = decode(data);

        outfile.open(argv[3], std::ios::binary);
        outfile << result;
        outfile.close();
    }

    return 0;

}



