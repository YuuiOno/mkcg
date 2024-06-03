#ifndef GRO_CPP
#define GRO_CPP

#include "gro.hpp"

#include <cmath>
#include <sstream>

namespace gro{
    
    // Functions
    float shrinkPosDigit(float f_){
        if(std::abs(f_/1000.0f)>=10.0f) throw LargeNumber("gro::shrinkPosDigit", f_);
        if(std::abs(f_*1000.0f)<1.0f)   f_=0.0f;

        return f_;
    }
    
    double shrinkPosDigit(double d_){
        if(std::abs(d_/1000.0)>=10.0) throw LargeNumber("gro::shrinkPosDigit", d_);
        if(std::abs(d_*1000.0)<1.0)   d_=0.0;

        return static_cast<double>(static_cast<float>(d_));
    }

    
    
    /*++++++++++++++++++++++*/
    /*    File Structure    */
    /*++++++++++++++++++++++*/
    // Constructr & Destructor
    File::File()
        : fs{}
        , last{0}
        , step_size{0}
        , locat{0}
        , title{}
        , moments{}
        , ttype{TITLE_AUTO}
        , btype{BOX_AUTO}
        , dtype{DATA_AUTO}
    {

        return;
    }
    

    File::File(const std::string& _istr)
        : fs        {_istr}
        , last      {0}
        , step_size {0}
        , locat     {0}
        , title     { }
        , moments   { }
        , ttype     {TITLE_AUTO}
        , btype     {BOX_AUTO}
        , dtype     {DATA_AUTO}
    {

        return;
    }
    
    
    File::File(const std::string& _istr, std::ios::openmode _opmd)
        : fs        {_istr, _opmd}
        , last      {0}
        , step_size {0}
        , locat     {0}
        , title     { }
        , moments   { }
        , ttype     {TITLE_AUTO}
        , btype     {BOX_AUTO}
        , dtype     {DATA_AUTO}
    {

    }


    File::~File(){
        last=0;
        step_size=0;
        locat=0;
    }

    
    // Altering Functions
    bool File::open(const std::string& _str, std::ios::openmode _opmd){
            
        // File Opening
        fs.open(_str, _opmd);
        if(!fs) throw FailedToOpenFile("gro::File::open", _str);

        return true;
    }


    bool File::acquire(){
        // File Check
        if(!fs) throw BadFile("gro::File::acquire");

        std::fstream::pos_type current=fs.tellg();
        fs.seekg(0, std::ios::end);
        last=fs.tellg();
        fs.seekg(0, std::ios::beg);

        Moment moment;
        if(!moment.read(fs) || last%fs.tellg()!=0) step_size=0;
        else                                       step_size=fs.tellg();

        fs.seekg(current, std::ios::beg);

        return true;
    }


    bool File::close(){
        // Destruct & Reconstruct
        this->~File();
        new(this) File();

        return true;
    }


    bool File::fclose(){
        this->fs.close();

        return true;
    }


    bool File::write(size_t _size, size_t _offset){
        // Vector Size Checking
        if(_offset+_size>moments.size()) throw OverArraySize("gro::File::write", moments.size(), _offset+_size);
        // File Checking
        if(!fs) throw BadFile("gro::File::write");

        // Writing
        if(_size==0) _size=moments.size();
        for(size_t a=0; a<_size; ++a){
            moments[_offset+a].write(fs);
        }
        locat=_offset+_size-1;

        return true;
    }
    
    
    bool File::read(size_t _size, size_t _offset){
        // File Checking
        if(!fs) throw BadFile("gro::File::write");
        
        // Informatiion Acquisition
        this->acquire();
        
        // Reading
        if(_size==0){
            moments.resize(_offset);
            while(last!=fs.tellg()){
                moments.push_back(Moment(fs));
            }
            locat=moments.size()-1;
        }else{
            moments.resize(_size+_offset);
            for(size_t a=_offset; a<moments.size(); ++a){
                moments[a].read(fs);
                locat=a;
            }
            locat=_offset+_size-1;
        }
        title=moments[0].title;

        return true;
    }
    
    
    bool File::seek(size_t _step){ 
        // Information Acquisition after Writing
        this->acquire();
   
        if(step_size!=0){
            fs.seekg(static_cast<std::fstream::pos_type>(_step*step_size), std::ios::beg);
        }else{
            fs.seekg(0);
            size_t alpha=0;
            Moment moment;
            while(alpha==_step){
                moment.read(fs);
                ++alpha;
            }
        }

        return true;
    }

    size_t File::tell(){
        // Information Acquisition after Writing
        this->acquire();
   
        size_t ot=0;
        
        std::fstream::pos_type current=fs.tellg();
        if(step_size==0){
            fs.seekg(0, std::ios::beg);
            while(current!=fs.tellg()){
                Moment moment(fs);
                ++ot;
            }
            fs.seekg(current, std::ios::beg);

        }else{
            ot=current/step_size;
        }

        return ot;
    }


    /*++++++++++++++++++++++++*/
    /*    Moment Structure    */
    /*++++++++++++++++++++++++*/
    // Constructor & Destructor
    Moment::Moment()
        : title     { }
        , time      {0.0}
        , step      {0}
        , particles { }
        , box       { }
        , ttype     {TITLE_AUTO}
        , btype     {BOX_AUTO}
        , dtype     {DATA_AUTO}
    {

    }
    
    Moment::Moment(size_t _num, const std::string& _title)
        : title     {_title}
        , time      {0.0}
        , step      {0}
        , particles {_num}
        , box       { }
        , ttype     {TITLE_AUTO}
        , btype     {BOX_AUTO}
        , dtype     {DATA_AUTO}
    {   
    
    }


    Moment::Moment(std::fstream& _ifs)
        : title     { }
        , time      {0.0}
        , step      {0}
        , particles { }
        , box       { }
        , ttype     {TITLE_AUTO}
        , btype     {BOX_AUTO}
        , dtype     {DATA_AUTO}
    {   
        this->read(_ifs);
    }


    Moment::~Moment(){
        //title.~basic_string();
        time=0.0;
        step=0;
        //particles.~vector();
        //box[0].~vec3();  box[1].~vec3();  box[2].~vec3();
        ttype=TITLE_AUTO;
        btype=BOX_AUTO;
        dtype=DATA_AUTO;

    }


    // Constant Functions
    std::string Moment::str(DataType _dtype, TitleType _ttype, BoxType _btype) const{
        
        if     (_dtype==DATA_AUTO)  _dtype=dtype;
        else if(_dtype==DATA_COORD) _dtype=DATA_COORD;
        else                        _dtype=DATA_FULL;

        if     (_ttype==TITLE_AUTO) _ttype=ttype;
        else if(_ttype==TITLE_TIME) _ttype=TITLE_TIME;
        else if(_ttype==TITLE_FULL) _ttype=TITLE_FULL;
        else                        _ttype=TITLE_NONE;
       
        if(_btype==BOX_AUTO){
            if      (box[0]==mv::vec3<double>()) _btype=BOX_NONE; 
            else if (box[1]==mv::vec3<double>() && box[2]==mv::vec3<double>()) _btype=BOX_CUBIC; 
            else    _btype=BOX_DIAGONAL; 
        }


        std::string ot;

        // 1st Line 
        switch(_ttype){
            case TITLE_FULL :
            {
                std::cout<<"TITLE_FULL"<<std::endl;
                char time_char[16]={'\0'};  std::sprintf(time_char, "%15.4lf", time);
                char step_char[15]={'\0'};  std::sprintf(step_char, "%14lu", step);
                ot=title+" t= "+time_char+" step= "+step_char+"\n";
                break;
            }
            case TITLE_TIME :
            {
                char time_char[16]={'\0'};  std::sprintf(time_char, "%15.4lf", time);
                ot=title+" t= "+time_char+"\n";
                break;
            }
            default :
            {
                ot=title+"\n";
                break;
            }
        }

        // 2nd Line
        char num_char[7]={'\0'};  std::sprintf(num_char, "%5d\n", num());
        ot+=num_char;

        // Particle Lines
        for(size_t a=0; a<num(); ++a) ot+=particles[a].str(_dtype)+"\n";

        // Last Line
        switch(_btype){
            case BOX_DIAGONAL :
            {
                char box_char[91]={'\0'};  std::sprintf(box_char, "%10.5lf%10.5lf%10.5lf%10.5lf%10.5lf%10.5lf%10.5lf%10.5lf%10.5lf", box[0].x, box[0].y, box[0].z, box[1].x, box[1].y, box[1].z, box[2].x, box[2].y, box[2].z);
                ot+=box_char;
                break;
            }
            case BOX_CUBIC :
            {
                char box_char[31]={'\0'};  std::sprintf(box_char, "%10.5lf%10.5lf%10.5lf", box[0].x, box[0].y, box[0].z);
                ot+=box_char;
                break;
            }
            default :
            {
                break;
            }
        }
    
        return ot;
    }


    bool Moment::write(std::fstream& _ofs) const{

        if(!_ofs) throw BadFile("gro::Moment::write");
        else      _ofs<<(*this)<<std::endl;

        return true;
    }


    // Altering Functions
    bool Moment::read(std::fstream& _ifs){
        std::string str1, str2;
        std::stringstream ss1;
        title.clear();

        // 1st Line
        std::getline(_ifs, str1);
        ss1<<str1;
        ss1>>str1;
        while(str1!="t=" && !ss1.eof()){
            title+=str1+" ";
            ss1>>str1;
        }
        title.pop_back();
        if(!ss1.eof()){ ss1>>time; ttype=TITLE_TIME; }
        else                       ttype=TITLE_NONE;
        if(!ss1.eof()){ ss1>>str1;  ss1>>step;  ttype=TITLE_FULL;}
        ss1.str("");  ss1.clear(std::stringstream::goodbit);
    
        // 2nd Line
        std::getline(_ifs, str1);
        ss1<<str1;
        size_t num_;
        ss1>>num_;
        particles.resize(num_);
        ss1.str("");  ss1.clear(std::stringstream::goodbit);

        // Particle Lines
        dtype=DATA_COORD;
        for(size_t a=0; a<num_; ++a){
            std::getline(_ifs, str1);
            particles[a].read(str1);
            if(particles[a].dtype==DATA_FULL) dtype=DATA_FULL;
        }
        
        // Last Line
        std::getline(_ifs, str1);
        if(str1.length()<=1){
            btype=BOX_NONE;

        }else if(str1.length()==30){
            btype=BOX_CUBIC;
            str1.insert(10, " ");
            str1.insert(21, " ");
            str1.insert(32, " ");
            ss1<<str1;
            ss1>>box[0].x;  ss1>>box[0].y;  ss1>>box[0].z;

        }else if(str1.length()==90){
            btype=BOX_DIAGONAL;
            str1.insert(10, " ");
            str1.insert(21, " ");
            str1.insert(32, " ");
            str1.insert(43, " ");
            str1.insert(54, " ");
            str1.insert(65, " ");
            str1.insert(76, " ");
            str1.insert(87, " ");
            ss1<<str1;
            ss1>>box[0].x;  ss1>>box[0].y;  ss1>>box[0].z; 
            ss1>>box[1].x;  ss1>>box[1].y;  ss1>>box[1].z; 
            ss1>>box[2].x;  ss1>>box[2].y;  ss1>>box[2].z;

        }else{
            btype=BOX_NONE;
        }

        return true;
    }


    /*++++++++++++++++++++++++++*/
    /*    Particle Structure    */
    /*++++++++++++++++++++++++++*/
    // Constructor & Destructor
    Particle::Particle()
        : res_num   {0}
        , res_name  { }
        , atom_name { }
        , atom_num  {0}
        , pos       { }
        , velo      { }
        , dtype     {DATA_AUTO}
    {   

    }

    Particle::Particle(
        size_t                _res_num,
        const std::string&      _res_name,
        const std::string&      _atom_name,
        size_t                _atom_num,
        const mv::vec3<double>& _pos,
        const mv::vec3<double>& _velo,
        DataType                _dtype
    )
        : res_num   {_res_num}
        , res_name  {_res_name}
        , atom_name {_atom_name}
        , atom_num  {_atom_num}
        , pos       {_pos}
        , velo      {_velo}
        , dtype     {_dtype}
    {

    }

    Particle::Particle(const std::string& _str){
        read(_str);

    }

    Particle::~Particle(){
        res_num=0;
        atom_num=0;

    }

    // Constant Function
    std::string Particle::str(DataType _dtype) const{
        if     (_dtype==DATA_AUTO)  _dtype=dtype;
        else if(_dtype==DATA_COORD) _dtype=DATA_COORD;
        else                        _dtype=DATA_FULL;

        std::string ot;
        char string[69]={"\0"};
        std::sprintf(string,"%5d%-5s%5s%5d%8.3f%8.3f%8.3f", res_num, res_name.c_str(), atom_name.c_str(), atom_num, pos.x, pos.y, pos.z);
        if(_dtype==DATA_FULL) std::sprintf(string+44,"%8.4f%8.4f%8.4f", velo.x, velo.y, velo.z);
        ot=string;
        
        return ot;
    }

    // Altering Function
    bool Particle::read(const std::string& _str){
        std::stringstream ss1;
        std::string str1;
        std::string dcmt=_str;
        if     (dcmt.length()==44) dtype=DATA_COORD;
        else if(dcmt.length()==68) dtype=DATA_FULL;
        else   throw InvaridParticleData("gro::Moment::read", dcmt.length());
        dcmt.insert(5, " ");
	    dcmt.insert(11, " ");
	    dcmt.insert(17, " ");
	    dcmt.insert(23, " ");
	    dcmt.insert(32, " ");
	    dcmt.insert(41, " ");
        if(dtype==DATA_FULL){
            dcmt.insert(50, " ");
	        dcmt.insert(59, " ");
	        dcmt.insert(68, " ");
        }
        ss1<<dcmt;
        ss1>>res_num;
        ss1>>str1; res_name=str1;
        ss1>>str1; atom_name=str1;
        ss1>>atom_num;
        ss1>>pos.x;  ss1>>pos.y;  ss1>>pos.z;
        if(dtype==DATA_FULL){
            ss1>>velo.x; ss1>>velo.y; ss1>>velo.z;
        }

        return true;
    } 
    
    

    /*+++++++++++++++++++++++++*/
    /*    Exception classes    */
    /*+++++++++++++++++++++++++*/
    template <typename T>
    std::string BaseException::numToString(const T& _num){
        std::stringstream ss1;
        ss1<<_num;

        return ss1.str();
    }


    FailedToOpenFile::FailedToOpenFile(const std::string& _str1, const std::string& _str2)
        : std::runtime_error{ std::stringstream{ _str1+":  Cannot Open File \""+_str2+"\"." }.str() }
    {

        return;
    }


    BadFile::BadFile(const std::string& _str)
        : std::runtime_error{ std::stringstream{ _str+":  Bad File Stream."}.str() }
    {

        return;
    }

    
    OverArraySize::OverArraySize(const std::string& _str, size_t _size, size_t _pointed)
        : std::runtime_error{ std::stringstream{ _str+":  Exceeding Array Size. (Pointed -> "+numToString<size_t>(_pointed)+", Array Size -> "+numToString<size_t>(_size)+")" }.str() }
    {

        return;
    }

    InvaridParticleData::InvaridParticleData(const std::string& _str, size_t _length)
        : std::runtime_error{ std::stringstream{ _str+":  Invarid Particle Data. (String Length -> "+numToString<size_t>(_length)+")" }.str() }
    {
        return;
    }
    
    LargeNumber::LargeNumber(const std::string& _str, double d_)
        : std::runtime_error{ std::stringstream{ _str+":  Too Large Number. (Number -> "+numToString<size_t>(d_)+")" }.str() }
    {
        return;
    }


}

// Gereral Functions
std::ostream& operator<<(std::ostream& _os, const gro::Moment& _mom){
 
    return _os<<_mom.str();
}

std::ostream& operator<<(std::ostream& _os, const gro::Particle& _particle){

    return _os<<_particle.str();
}
#endif
