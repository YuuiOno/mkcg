#ifndef GRO_HPP
#define GRO_HPP

#include <fstream>
#include <vector>
#include "mv/vec3.hpp"

namespace gro{

    /*+++++++++++++++++++*/
    /*    Declaration    */
    /*+++++++++++++++++++*/
    // Structures
    struct File;
    struct Moment;
    struct Particle;
        
    // Enumerations
    enum TitleType { TITLE_AUTO, TITLE_NONE, TITLE_TIME, TITLE_FULL };
    enum BoxType   { BOX_AUTO,   BOX_NONE,   BOX_CUBIC,  BOX_DIAGONAL };
    enum DataType  { DATA_AUTO,  DATA_COORD, DATA_FULL };

    // Exception Classes
    class BaseException;
    class FailedToOpenFile;
    class BadFile;
    class OverArraySize;
    class InvaridParticleData;
    class LargeNumber;

    // Functions
    float  shrinkPosDigit(float);
    double shrinkPosDigit(double);

    /*++++++++++++++++++++++*/
    /*    File Structure    */
    /*++++++++++++++++++++++*/
    struct File{

        // Definition
        std::fstream           fs;
        std::fstream::pos_type last;
        std::fstream::pos_type step_size;
        size_t                 locat;
        std::string            title;
        std::vector<Moment>    moments;
        TitleType              ttype;
        BoxType                btype;
        DataType               dtype;

        // Constructor & Destructor
        File();
        File(const std::string&);
        File(const std::string&, std::ios::openmode);
        ~File();
    
        // Altering Functions
        bool open(const std::string&, std::ios::openmode=std::ios::in|std::ios::out);
        bool acquire();
        bool close();
        bool fclose();
        bool write(size_t=0, size_t=0);
        bool read(size_t=0, size_t=0);
        bool seek(size_t);
        size_t tell();
    };


    /*++++++++++++++++++++++++*/
    /*    Moment Structure    */
    /*++++++++++++++++++++++++*/
    struct Moment{
        
        // Definition
        std::string           title;
        double                time;
        size_t                step;
        std::vector<Particle> particles;
        mv::vec3<double>      box[3];
        TitleType             ttype;
        BoxType               btype;
        DataType              dtype;

        // Constract & Destructor
        Moment();
        Moment(size_t, const std::string& ="");
        Moment(std::fstream&);
        ~Moment();

        // Constant Functions
        size_t num (void) const noexcept{
            return particles.size();
        };
        std::string str(DataType=DATA_AUTO, TitleType=TITLE_AUTO, BoxType=BOX_AUTO) const;
        bool write(std::fstream&) const; 

        // Altering Fcuntions
        bool read(std::fstream&);

    };


    /*++++++++++++++++++++++++++*/
    /*    Particle Structure    */
    /*++++++++++++++++++++++++++*/
    struct Particle{
	    
        // Definition
        size_t           res_num;
    	std::string      res_name;
	    std::string      atom_name;
	    size_t           atom_num;
	    mv::vec3<double> pos;
	    mv::vec3<double> velo;
        DataType         dtype;

        // Constructor & Destructor
        Particle();
        Particle(const std::string&);
        Particle(size_t, const std::string&, const std::string&, size_t, const mv::vec3<double>&, const mv::vec3<double>&, DataType=DATA_AUTO);
        ~Particle();

        // Constant Function
        std::string str(DataType=DATA_AUTO) const;

        // Altering Function
        bool read(const std::string&);

    };
    
    
    /*+++++++++++++++++++++++++*/
    /*    Exception classes    */
    /*+++++++++++++++++++++++++*/
    class BaseException{
        protected :
        template <typename T>
        std::string numToString(const T&);
    };

    class FailedToOpenFile    : public BaseException, public std::runtime_error{
        public :
        FailedToOpenFile(const std::string&, const std::string&);
    };

    class BadFile: public BaseException, public std::runtime_error{
        public :
        BadFile(const std::string&);   
    };

    class OverArraySize       : public BaseException, public std::runtime_error{
        public :
        OverArraySize(const std::string&, size_t, size_t);    
    };

    class InvaridParticleData : public BaseException, public std::runtime_error{
        public :
        InvaridParticleData(const std::string&, size_t);    
    };
    
    class LargeNumber : public BaseException, public std::runtime_error{
        public :
        LargeNumber(const std::string&, double);    
    };


}

// General Functions
std::ostream& operator<<(std::ostream&, const gro::Moment&);
std::ostream& operator<<(std::ostream&, const gro::Particle&);

//#include "gro.cpp"

#endif
