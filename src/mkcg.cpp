#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <cfloat>

#include "gro.hpp"
#include "mv/vec2.hpp"
#include "mv/mat22.hpp"
#include "mv/conversion.cpp"

int main(int argc, char** argv){
   
    //++++++++++++++++++++++//
    //    Default Values    //
    //++++++++++++++++++++++//
    enum Target{ CNT, CNTGRA, GRA } target=Target::CNT;
    std::string      output="cntgra";
    double           length=3.0f;
    uint32_t         chiral[2]={8,8};
    double           width=0.0f;  bool enable_width=false;
    double           height=0.0f; bool enable_height=false;
    uint32_t         nrexcl=3;
    bool             enable_info=false;
    uint32_t         layer_num=5;
    double           layer_dist=0.45;
    uint32_t         hole=3;
    mv::vec3<double> box;    bool enable_box=false;    bool enable_boxz=false;
    //mv::vec3<double> center;
    struct Charge{ double amount;        uint32_t number; }       charge={0.0f, 0};
    struct Cname { std::string mol_name; std::string atom_name; } cname={"CNT", "CJ"};
    struct Gname { std::string mol_name; std::string atom_name; } gname={"GRA", "CG"};


    //+++++++++++++++++++++++++//
    //    Command Operation    //
    //+++++++++++++++++++++++++//
    {
        for(int32_t a=1; a<argc; ++a){
            std::string str1=argv[a];

            if(str1=="-t" || str1=="--target"){
                std::string str2=argv[a+1];
                if     (str2=="CNT")    target=Target::CNT;
                else if(str2=="CNTGRA") target=Target::CNTGRA;
                else if(str2=="GRA")    target=Target::GRA;
                else{
                    std::cerr<<"Unknow Target"<<std::endl;
                    std::exit(-1);
                }
                ++a;

            }else if(str1=="-o" || str1=="--output"){
                output=argv[a+1];
                ++a;

            }else if(str1=="-bz" || str1=="--boxz"){
                std::stringstream ss1;
                ss1<<argv[a+1];
                ss1>>box.z;
                enable_boxz=true;
                ++a;
 
            }else if(str1=="-nex" || str1=="--nrexcl"){
                std::stringstream ss1;
                ss1<<argv[a+1];
                ss1>>nrexcl;
                ++a;
               
            }else if(str1=="-h" || str1=="--help"){
                std::cerr<<"MD_MKCG Ver.2.0.0"<<std::endl;
                std::cerr<<"ONO Yûi  2021/10/31"<<std::endl;
                std::cerr<<"[Common Option]"<<std::endl;
                std::cerr<<"-t     --target   <Target>                      (CNT,CNTGRA,GRA) def:CNT"<<std::endl;
                std::cerr<<"-o     --output   <File String>                 (std::string)    def:\"cntgra\""<<std::endl;
                std::cerr<<"-bz    --boxz     <System Box Z (Auto XY) [nm]> (double)         def:[none]"<<std::endl;
                std::cerr<<"-nex   --nrexcl   <Number of Exclusion>         (uint32_t)       def:3"<<std::endl;
                std::cerr<<"-h     --help     <Display Help>                ( )              def:[off]"<<std::endl; 
                std::cerr<<"-i     --inform   <Display Information>         ( )              def:[off]"<<std::endl;
                std::cerr<<std::endl;
                std::cerr<<"[Option of Target:CNT]"<<std::endl;
                std::cerr<<"-l     --length      <CNT Length [nm]>              (double)           def:3.0"<<std::endl;
                std::cerr<<"-c     --chiral      <CNT Chiral [1,1]>             (uint32_t[2])      def:8, 8"<<std::endl;
                std::cerr<<"-cn    --cnt_name    <CNT Molname & Atomname>       (std::string[2])   def:CNT, CJ"<<std::endl;
                std::cerr<<"-chg   --charge      <Charge Amount & Number [e,1]> (double, uint32_t) def:0.0, 0"<<std::endl;
                std::cerr<<"-b     --box         <System Box [nm]>              (double)           def:[none]"<<std::endl;
                std::cerr<<std::endl;
                std::cerr<<"[Option of Target:CNTGRA]"<<std::endl;
                std::cerr<<"-l     --length          <CNT Length [nm]>              (double)           def:3.0"<<std::endl;
                std::cerr<<"-c     --chiral          <CNT Chiral [1,1]>             (uint32_t[2])      def:8, 8"<<std::endl;
                std::cerr<<"-cn    --cnt_name        <CNT Molname & Atomname>       (std::string[2])   def:CNT, CJ"<<std::endl;
                std::cerr<<"-chg   --charge          <Charge Amount & Number [e,1]> (double, uint32_t) def:0.0, 0"<<std::endl;
                std::cerr<<"-gw    --graphene_width  <Graphene Width [nm]>          (double)           def:[auto]"<<std::endl;
                std::cerr<<"-gh    --graphene_height <Graphene Height [nm]>         (double)           def:[auto]"<<std::endl;
                std::cerr<<"-gn    --graphene_name   <Graphene Molname & Atomname>  (std::string[2])   def:GRA, CG"<<std::endl;
                std::cerr<<std::endl;
                std::cerr<<"[Option of Target:GRA]"<<std::endl;
                std::cerr<<"-gw    --graphene_width      <Graphene Width [nm]>          (double)         def:[auto]"<<std::endl;
                std::cerr<<"-gh    --graphene_height     <Graphene Height [nm]>         (double)         def:[auto]"<<std::endl;
                std::cerr<<"-gn    --graphene_name       <Graphene Molname & Atomname>  (std::string[2]) def:GRA, CG"<<std::endl;
                std::cerr<<"-gl    --graphene_layer_num  <Graphene Layer Number [1]>    (uint32_t)       def:5"<<std::endl;
                std::cerr<<"-gd    --graphene_layer_dist <Generate Layer Distance [nm]> (double)         def:0.45"<<std::endl;
                std::cerr<<"-ghh   --graphene_hole       <Graphene Hole Hex Size [1]>   (uint32_t)       def:3"<<std::endl;
                exit(EXIT_SUCCESS);

            }else if(str1=="-i" || str1=="--inform"){
                enable_info=true;
 
            }else if(str1=="-l" || str1=="--length"){
                std::stringstream ss1;
                ss1<<argv[a+1];
                ss1>>length;
                ++a;

            }else if(str1=="-c" || str1=="--chiral"){
                std::stringstream ss1;
                ss1<<argv[a+1]<<" "<<argv[a+2];
                ss1>>chiral[1];
                ss1>>chiral[0];
                a+=2;

            }else if(str1=="-cn" || str1=="--cnt_name"){
                std::stringstream ss1;
                ss1<<argv[a+1]<<" "<<argv[a+2];
                ss1>>cname.mol_name;
                ss1>>cname.atom_name;
                a+=2;

            }else if(str1=="-chg" || str1=="--charge"){
                std::stringstream ss1;
                ss1<<argv[a+1]<<" "<<argv[a+2];
                ss1>>charge.amount;
                ss1>>charge.number;
                a+=2;
        
            }else if(str1=="-b" || str1=="--box"){
                std::stringstream ss1;
                ss1<<argv[a+1]<<" "<<argv[a+2]<<" "<<argv[a+3];
                ss1>>box.x;  ss1>>box.y;  ss1>>box.z;
                enable_box=true;
                a+=3;

            }else if(str1=="-gw" || str1=="--graphene_width"){
                std::stringstream ss1;
                ss1<<argv[a+1];
                ss1>>width;
                enable_width=true;
                ++a;

            }else if(str1=="-gh" || str1=="--graphene_Height"){
                std::stringstream ss1;
                ss1<<argv[a+1];
                ss1>>height;
                enable_height=true;
                ++a;
            
            }else if(str1=="-gn" || str1=="--graphene_name"){
                std::stringstream ss1;
                ss1<<argv[a+1]<<" "<<argv[a+2];
                ss1>>gname.mol_name;
                ss1>>gname.atom_name;
                a+=2;

            }else if(str1=="-gl" || str1=="--graphene_layer_num"){
                std::stringstream ss1;
                ss1<<argv[a+1];
                ss1>>layer_num;
                ++a;

            }else if(str1=="-gd" || str1=="--graphene_layer_distance"){
                std::stringstream ss1;
                ss1<<argv[a+1];
                ss1>>layer_dist;
                ++a;

            }else if(str1=="-ghh" || str1=="--graphene_hole"){
                std::stringstream ss1;
                ss1<<argv[a+1];
                ss1>>hole;
                ++a;            
              
            }else{
                std::cerr<<"UNKNOWN OPTION : "<<argv[a]<<std::endl;
                std::exit(-1);
            }
        }
    }


    //+++++++++++++++++++++++//
    //    Constant Values    //
    //+++++++++++++++++++++++//
    constexpr double ver_period=0.142*3.0;            //[nm]
    constexpr double ver_step  =0.142*0.5;            //[nm]
    const     double hor_period=0.142*std::sqrt(3.0); //[nm]


    //++++++++++++++++++++++++++++++++++++//
    //    Calculation of Atom Position    //
    //++++++++++++++++++++++++++++++++++++//
    gro::Moment mom;
    std::vector<size_t> resid_separ;
    if(target==Target::CNT){
        if(enable_info) std::cout<<"(1) Calculating Atom Position (Target: CNT)"<<std::endl;
        double diameter;
        double radius;
        double act_length=0.;
    
        mv::vec2<double> chvec=mv::vec2<double>{1.0, 0.0}*chiral[0]*hor_period + mv::vec2<double>{std::cos(M_PI*5.0/3.0), std::sin(M_PI*5.0/3.0)}*chiral[1]*hor_period;
        mv::vec2<double> vtvec=mv::vec2<double>{-chvec.normal().y, chvec.normal().x}*length;
        diameter=chvec.norm()/M_PI;
        radius=diameter*0.5;
    
        // Temporary Position before Rotation
        std::vector<mv::vec2<double>> temp_coords;
        {
            const double effrad=(chvec+vtvec).norm()+0.071;
            double basey=-static_cast<double>(static_cast<uint32_t>(effrad/(ver_period)))*(ver_period);
            mv::vec2<double> xy={0.0, basey};
            uint32_t ycount=0;
            while(basey<=effrad){
                while(xy.norm()<=effrad){
                    if(ycount%2==0){
                        temp_coords.push_back(xy);
                        xy+=mv::vec2<double>{hor_period*0.5, +ver_step};
                        temp_coords.push_back(xy);
                        xy+=mv::vec2<double>{hor_period*0.5, -ver_step};
                    }else{
                        temp_coords.push_back(xy);
                        xy+=mv::vec2<double>{hor_period*0.5, -ver_step};
                        temp_coords.push_back(xy);
                        xy+=mv::vec2<double>{hor_period*0.5, +ver_step};
                    }
                }    
                if(ycount%2==0) basey+=0.142*2;
                else            basey+=0.142;
                xy={0.0f, basey};
                ++ycount;
            }
        }
    
    
        // Rotation and Extraction
        std::vector<mv::vec2<double>> rot_coords;
        {
            double cos=chvec.x/chvec.norm();
            double sin=chvec.y/chvec.norm();
            mv::mat22<double> rotate{cos, sin, -sin, cos};
    
            for(uint32_t a=0; a<temp_coords.size(); ++a){
                mv::vec2<double> rot_xy=(rotate | temp_coords[a]).image(gro::shrinkPosDigit);
                if(
                    rot_xy.x>=0.0f && rot_xy.x<static_cast<float>(diameter*M_PI) &&
                    rot_xy.y>=0.0f && rot_xy.y<static_cast<float>(length)
                ){
                    if(act_length<rot_xy.y) act_length=rot_xy.y;
                    rot_coords.push_back(rot_xy);
                }
            }
            temp_coords.~vector();
            new(&temp_coords) std::vector<double>();
        }
      
    
        // Convert to the Cylindrical Coordinate
        mom.~Moment();
        new(&mom) gro::Moment(rot_coords.size(), "Made by mkcg");
        for(uint32_t a=0; a<rot_coords.size(); ++a){
            mv::vec2<double>& rot_xy=rot_coords[a];
            mv::vec3<double>  cl_xy{diameter/2.0*std::cos(rot_xy.x*2.0/diameter), diameter/2.0*std::sin(rot_xy.x*2.0/diameter), rot_xy.y};
            mom.particles[a].res_num=1;
            mom.particles[a].res_name=cname.mol_name;
            mom.particles[a].atom_name=cname.atom_name;
            mom.particles[a].atom_num=a+1;
            mom.particles[a].pos=cl_xy;
        }
        rot_coords.~vector();
        new(&rot_coords) std::vector<mv::vec2<double>>();
        
    
        
        // Find the Un-satisfied carbon atoms
        struct Neighb{ uint16_t count=0; size_t list[3]; };
        std::vector<Neighb> neighb(mom.num());
        {
    
            for(size_t a=0; a<mom.num(); ++a){
                gro::Particle& pa_=mom.particles[a];
        
                for(size_t b=a+1; b<mom.num(); ++b){
                    gro::Particle& pb_=mom.particles[b];
    
                    constexpr float blengpw2=0.15*0.15; 
                    if((pa_.pos-pb_.pos).square()<blengpw2){
                        switch(neighb[a].count){
                            case 0 : neighb[a].list[0]=pb_.atom_num;  ++neighb[a].count;  break;
                            case 1 : neighb[a].list[1]=pb_.atom_num;  ++neighb[a].count;  break;
                            case 2 : neighb[a].list[2]=pb_.atom_num;  ++neighb[a].count;  break;
                            default: std::cerr<<"Failed to make neighbs"<<std::endl;   std::exit(EXIT_FAILURE);  break;
                        }
                        switch(neighb[b].count){
                            case 0 : neighb[b].list[0]=pb_.atom_num;  ++neighb[b].count;  break;
                            case 1 : neighb[b].list[1]=pb_.atom_num;  ++neighb[b].count;  break;
                            case 2 : neighb[b].list[2]=pb_.atom_num;  ++neighb[b].count;  break;
                            default: std::cerr<<"Failed to make neighbs"<<std::endl;   std::exit(EXIT_FAILURE);  break;
                        }
                    }   
                }
            }
            // Charging
            if(charge.number!=0){
                for(size_t a=0; a<charge.number; ++a){
    
                    const double theta=2.0*M_PI*static_cast<double>(a)/static_cast<double>(charge.number);
                    const mv::vec3<double> xx={ std::cos(theta), std::sin(theta), 0.0 };
                    const mv::vec3<double> yy={ std::cos(theta), std::sin(theta), length };
                    double min_p=DBL_MAX;
                    double min_m=DBL_MAX;
                    size_t minid_p, minid_m;
    
                    for(size_t b=0; b<neighb.size(); ++b){
                        gro::Particle& par=mom.particles[b];
                        if(neighb[b].count<3 && par.pos.z<length*0.5 && (xx-par.pos).square()<min_p){
                            min_p=(xx-par.pos).square();
                            minid_p=b;
                        }
                        if(neighb[b].count<3 && par.pos.z>=length*0.5 && (yy-par.pos).square()<min_m){
                            min_m=(yy-par.pos).square();
                            minid_m=b;
                        }
                    }
                    char charge_val[4]={'\0'};
                    std::sprintf(charge_val, "%03d", static_cast<uint32_t>(charge.amount*100.0));
                    mom.particles[minid_p].atom_name=std::string("CP")+charge_val;
                    mom.particles[minid_m].atom_name=std::string("CM")+charge_val;
                }
            }
             
            // Box & CNT Position
            mv::vec3<mv::sca> trans;
            if(enable_box){
                mom.box[0]=box;
                trans=box*0.5-mv::vec3<mv::sca>{0., 0., act_length*0.5};
    
            }else if(enable_boxz){
                mom.box[0]=(box={diameter, diameter, box.z});
                trans={radius, radius, (box.z-act_length)*0.5};
        
            }else{
                mom.box[0]=(box={diameter, diameter, act_length});
                trans={radius, radius, 0.};
            }
            for(size_t a=0; a<mom.num(); ++a) mom.particles[a].pos+=trans;
        }
    }


    if(target==Target::CNTGRA){
        if(enable_info) std::cout<<"(1) Calculating Atom Position (Target: CNTGRA)"<<std::endl;
        double diameter;
        double radius;
        double act_length=0.;
    
        mv::vec2<double> chvec=mv::vec2<double>{1.0, 0.0}*chiral[0]*hor_period + mv::vec2<double>{std::cos(M_PI*5.0/3.0), std::sin(M_PI*5.0/3.0)}*chiral[1]*hor_period;
        mv::vec2<double> vtvec=mv::vec2<double>{-chvec.normal().y, chvec.normal().x}*length;
        diameter=chvec.norm()/M_PI;
        radius=diameter*0.5;
   
        //+    CNT     +//
        // Temporary Position before Rotation
        std::vector<mv::vec2<double>> temp_coords;
        {
            const double effrad=(chvec+vtvec).norm()+0.071;
            double basey=-static_cast<double>(static_cast<uint32_t>(effrad/(ver_period)))*(ver_period);
            mv::vec2<double> xy={0.0, basey};
            uint32_t ycount=0;
            while(basey<=effrad){
                while(xy.norm()<=effrad){
                    if(ycount%2==0){
                        temp_coords.push_back(xy);
                        xy+=mv::vec2<double>{hor_period*0.5, +ver_step};
                        temp_coords.push_back(xy);
                        xy+=mv::vec2<double>{hor_period*0.5, -ver_step};
                    }else{
                        temp_coords.push_back(xy);
                        xy+=mv::vec2<double>{hor_period*0.5, -ver_step};
                        temp_coords.push_back(xy);
                        xy+=mv::vec2<double>{hor_period*0.5, +ver_step};
                    }
                }    
                if(ycount%2==0) basey+=0.142*2;
                else            basey+=0.142;
                xy={0.0f, basey};
                ++ycount;
            }
        }
    
    
        // Rotation and Extraction
        std::vector<mv::vec2<double>> rot_coords;
        {
            double cos=chvec.x/chvec.norm();
            double sin=chvec.y/chvec.norm();
            mv::mat22<double> rotate{cos, sin, -sin, cos};
    
            for(uint32_t a=0; a<temp_coords.size(); ++a){
                mv::vec2<double> rot_xy=(rotate | temp_coords[a]).image(gro::shrinkPosDigit);
                if(
                    rot_xy.x>=0.0f && rot_xy.x<static_cast<float>(diameter*M_PI) &&
                    rot_xy.y>=0.0f && rot_xy.y<static_cast<float>(length)
                ){
                    if(act_length<rot_xy.y) act_length=rot_xy.y;
                    rot_coords.push_back(rot_xy);
                }
            }
            temp_coords.~vector();
            new(&temp_coords) std::vector<double>();
        }
      
    
        // Convert to the Cylindrical Coordinate
        mom.~Moment();
        new(&mom) gro::Moment(rot_coords.size(), "Made by mkcg");
        for(uint32_t a=0; a<rot_coords.size(); ++a){
            mv::vec2<double>& rot_xy=rot_coords[a];
            mv::vec3<double>  cl_xy{diameter/2.0*std::cos(rot_xy.x*2.0/diameter), diameter/2.0*std::sin(rot_xy.x*2.0/diameter), rot_xy.y};
            mom.particles[a].res_num=1;
            mom.particles[a].res_name=cname.mol_name;
            mom.particles[a].atom_name=cname.atom_name;
            mom.particles[a].atom_num=a+1;
            mom.particles[a].pos=cl_xy;
        }
        rot_coords.~vector();
        new(&rot_coords) std::vector<mv::vec2<double>>();
        
    
        
        // Find the Un-satisfied carbon atoms
        struct Neighb{ uint16_t count=0; size_t list[3]; };
        std::vector<Neighb> neighb(mom.num());
        {
    
            for(size_t a=0; a<mom.num(); ++a){
                gro::Particle& pa_=mom.particles[a];
        
                for(size_t b=a+1; b<mom.num(); ++b){
                    gro::Particle& pb_=mom.particles[b];
    
                    constexpr float blengpw2=0.15*0.15; 
                    if((pa_.pos-pb_.pos).square()<blengpw2){
                        switch(neighb[a].count){
                            case 0 : neighb[a].list[0]=pb_.atom_num;  ++neighb[a].count;  break;
                            case 1 : neighb[a].list[1]=pb_.atom_num;  ++neighb[a].count;  break;
                            case 2 : neighb[a].list[2]=pb_.atom_num;  ++neighb[a].count;  break;
                            default: std::cerr<<"Failed to make neighbs"<<std::endl;   std::exit(EXIT_FAILURE);  break;
                        }
                        switch(neighb[b].count){
                            case 0 : neighb[b].list[0]=pb_.atom_num;  ++neighb[b].count;  break;
                            case 1 : neighb[b].list[1]=pb_.atom_num;  ++neighb[b].count;  break;
                            case 2 : neighb[b].list[2]=pb_.atom_num;  ++neighb[b].count;  break;
                            default: std::cerr<<"Failed to make neighbs"<<std::endl;   std::exit(EXIT_FAILURE);  break;
                        }
                    }   
                }
            }
            // Charging
            if(charge.number!=0){
                for(size_t a=0; a<charge.number; ++a){
    
                    const double theta=2.0*M_PI*static_cast<double>(a)/static_cast<double>(charge.number);
                    const mv::vec3<double> xx={ std::cos(theta), std::sin(theta), 0.0 };
                    const mv::vec3<double> yy={ std::cos(theta), std::sin(theta), length };
                    double min_p=DBL_MAX;
                    double min_m=DBL_MAX;
                    size_t minid_p, minid_m;
    
                    for(size_t b=0; b<neighb.size(); ++b){
                        gro::Particle& par=mom.particles[b];
                        if(neighb[b].count<3 && par.pos.z<length*0.5 && (xx-par.pos).square()<min_p){
                            min_p=(xx-par.pos).square();
                            minid_p=b;
                        }
                        if(neighb[b].count<3 && par.pos.z>=length*0.5 && (yy-par.pos).square()<min_m){
                            min_m=(yy-par.pos).square();
                            minid_m=b;
                        }
                    }
                    char charge_val[4]={'\0'};
                    std::sprintf(charge_val, "%03d", static_cast<uint32_t>(charge.amount*100.0));
                    mom.particles[minid_p].atom_name=std::string("CP")+charge_val;
                    mom.particles[minid_m].atom_name=std::string("CM")+charge_val;
                }
            }
             
            // Box & CNT Position
            mv::vec3<mv::sca> trans;
            if(enable_boxz){
                mom.box[0]=(box={diameter, diameter, box.z});
                trans={radius, radius, (box.z-act_length)*0.5};
        
            }else{
                mom.box[0]=(box={diameter, diameter, act_length});
                trans={radius, radius, 0.};
            }
            for(size_t a=0; a<mom.num(); ++a) mom.particles[a].pos+=trans;
        }


        //+   Graphene    +//
        // Set Auto Graphene Width & Height
        if(!enable_width)  width =diameter+3.;
        if(!enable_height) height=diameter+3.;
        
        // Constant Values
        const uint32_t hor_num=static_cast<uint32_t>(width/hor_period);
        const double   hor=static_cast<double>(hor_num)*hor_period;
        const uint32_t ver_num=static_cast<uint32_t>(height/ver_period)*2; 
        const double   ver=static_cast<double>(ver_num)*ver_period*0.5;
        const size_t   the_res_num=(cname.mol_name==gname.mol_name ? 1 : 2);

        // Move the CNT coordinate if CNT_CETER = [Auto]
        for(size_t a=0; a<mom.num(); ++a) mom.particles[a].pos+=mv::vec3<double>{ hor*0.5-radius, ver*0.5-radius, 0.0};
        
        if(enable_boxz){
            mom.box[0]=(box={ hor, ver, box.z });
        }else{
            mom.box[0]=(box={ hor, ver, act_length });
        }
        mv::vec3<mv::sca> center=box*0.5;
         
        // Put the Under Carbon Atoms of Graphene
        {
            double basey=0.0;
            mv::vec2<double> xy={0.0, basey};
            uint32_t ycount=0;
            resid_separ.push_back(mom.num());
            size_t par_count=mom.num()+1;
            for(uint32_t a=0; a<ver_num; ++a){
                for(uint32_t b=0; b<hor_num; ++b){
                    gro::Particle par;
                    par.res_name=gname.mol_name;
                    par.res_num=the_res_num;
                    par.atom_num=par_count;
                    par.atom_name=gname.atom_name;
                    mv::vec3<double> base={0.0, 0.0, center.z-act_length*0.5 };
                    par.pos=base+mv::vec3<double>{xy, 0.0};
                    const double rr12=(radius+0.142)*(radius+0.142);
                    if(ycount%2==0){
                        if((center.xy()-par.pos.xy()).square()>=rr12){ mom.particles.push_back(par); par.atom_num=++par_count; };
                        xy+=mv::vec2<double>{hor_period*0.5, +ver_step};
                        par.pos=base+mv::vec3<double>{xy, 0.0};
        

                        if((center.xy()-par.pos.xy()).square()>=rr12){ mom.particles.push_back(par); par.atom_num=++par_count; };
                        xy+=mv::vec2<double>{hor_period*0.5, -ver_step};
                        par.pos=base+mv::vec3<double>{xy, 0.0};

                    }else{
                        if((center.xy()-par.pos.xy()).square()>=rr12){ mom.particles.push_back(par); par.atom_num=++par_count; };
                        xy+=mv::vec2<double>{hor_period*0.5, -ver_step};
                        par.pos=base+mv::vec3<double>{xy, 0.0};

                        if((center.xy()-par.pos.xy()).square()>=rr12){ mom.particles.push_back(par); par.atom_num=++par_count; };
                        xy+=mv::vec2<double>{hor_period*0.5, +ver_step};
                        par.pos=base+mv::vec3<double>{xy, 0.0};

                    }
                }
                if(ycount%2==0) basey+=0.142*2;
                else            basey+=0.142;
                xy={0.0f, basey};
                ++ycount;
            }
        }
        

        // Put the Upper Carbon Atoms of Graphene
        {
            double basey=0.0;
            mv::vec2<double> xy={0.0, basey};
            uint32_t ycount=0;
            resid_separ.push_back(mom.num());
            size_t par_count=mom.num()+1;
            for(uint32_t a=0; a<ver_num; ++a){
                for(uint32_t b=0; b<hor_num; ++b){
                    gro::Particle par;
                    par.res_name=gname.mol_name;
                    par.res_num=(the_res_num==2 ? 3 : 1);
                    par.atom_num=par_count;
                    par.atom_name=gname.atom_name;
                    mv::vec3<double> base={0.0, 0.0, center.z+act_length*0.5 };
                    par.pos=base+mv::vec3<double>{xy, 0.0};
                    const double rr12=(radius+0.142)*(radius+0.142);
                    if(ycount%2==0){
                        if((center.xy()-par.pos.xy()).square()>=rr12){ mom.particles.push_back(par); par.atom_num=++par_count; };
                        xy+=mv::vec2<double>{hor_period*0.5, +ver_step};
                        par.pos=base+mv::vec3<double>{xy, 0.0};

                        if((center.xy()-par.pos.xy()).square()>=rr12){ mom.particles.push_back(par); par.atom_num=++par_count; };
                        xy+=mv::vec2<double>{hor_period*0.5, -ver_step};
                        par.pos=base+mv::vec3<double>{xy, 0.0};

                    }else{
                        if((center.xy()-par.pos.xy()).square()>=rr12){ mom.particles.push_back(par); par.atom_num=++par_count; };
                        xy+=mv::vec2<double>{hor_period*0.5, -ver_step};
                        par.pos=base+mv::vec3<double>{xy, 0.0};

                        if((center.xy()-par.pos.xy()).square()>=rr12){ mom.particles.push_back(par); par.atom_num=++par_count; };
                        xy+=mv::vec2<double>{hor_period*0.5, +ver_step};
                        par.pos=base+mv::vec3<double>{xy, 0.0};

                    }
                }
                if(ycount%2==0) basey+=0.142*2;
                else            basey+=0.142;
                xy={0.0f, basey};
                ++ycount;
            }
        }
    }


    if(target==Target::GRA){
        if(enable_info) std::cout<<"(1) Calculating Atom Position (Target: GRA)"<<std::endl;
        
        if(!enable_width)  width =(static_cast<double>(hole)*2-1)*0.142+3.;
        if(!enable_height) height=(static_cast<double>(hole)*2-1)*0.142+3.;
        
        // Constant Values
        const uint32_t hor_num=static_cast<uint32_t>(width/hor_period);
        const double   hor=static_cast<double>(hor_num)*hor_period;
        const uint32_t ver_num=static_cast<uint32_t>(height/ver_period)*2; 
        const double   ver=static_cast<double>(ver_num)*ver_period*0.5;
        const double   length=layer_dist*static_cast<double>(layer_num-1);

        if(enable_boxz){
            mom.box[0]=(box={ hor, ver, box.z });
        }else{
            mom.box[0]=(box={ hor, ver, length<0.1 ? 0.1 : length });
        }

        mv::vec3<mv::sca> center=box*0.5;
         
        // Put Carbon Atoms of Graphene
        std::vector<mv::vec3<double>> hex_centers; 
        {
            double basez=(box.z-length)*0.5;
                
            if(!enable_boxz and layer_num==1) basez=0.0;
            double basey=0.0;
            mv::vec2<double> xy={0.0, basey};
            uint32_t ycount=0;
             for(uint32_t a=0; a<ver_num; ++a){
                for(uint32_t b=0; b<hor_num; ++b){
                    mv::vec3<double> base={0.0, 0.0, center.z-length*0.5 };
                    mv::vec3<double> pos=base+mv::vec3<double>{xy, 0.0};
                    
                    if(ycount%2==0){
                        hex_centers.push_back(pos+mv::vec3<double>(0., ver_step*2, 0.));
                        xy+=mv::vec2<double>{hor_period*0.5, +ver_step};
                        pos=base+mv::vec3<double>{xy, 0.0};
        
                        xy+=mv::vec2<double>{hor_period*0.5, -ver_step};
                        pos=base+mv::vec3<double>{xy, 0.0};

                    }else{
                        xy+=mv::vec2<double>{hor_period*0.5, -ver_step};
                        pos=base+mv::vec3<double>{xy, 0.0};

                        hex_centers.push_back(pos+mv::vec3<double>(0., ver_step*2, 0.));
                        xy+=mv::vec2<double>{hor_period*0.5, +ver_step};
                        pos=base+mv::vec3<double>{xy, 0.0};

                    }
                }
                if(ycount%2==0) basey+=0.142*2;
                else            basey+=0.142;
                xy={0.0f, basey};
                ++ycount;
            }
        }

        mv::vec3<double> hole_center;
        {
            mv::vec3<double> center{hor*0.5, ver*0.5, hex_centers[0].z};
            constexpr double lenp2=0.142*0.142;

            for(size_t a=0; a<hex_centers.size(); ++a){
                if((center-hex_centers[a]).square()<=lenp2){
                    hole_center=hex_centers[a];
                    break;
                }
            }
        }
        
        {
            const double radius=(static_cast<double>(hole)+0.5)*0.142;
            double basez=(box.z-length)*0.5;
            for(uint32_t c=0; c<layer_num; ++c){

                if(!enable_boxz and layer_num==1) basez=0.0;
                double basey=0.0;
                mv::vec2<double> xy={0.0, basey};
                uint32_t ycount=0;
                resid_separ.push_back(mom.num());
                size_t par_count=mom.num()+1;

                for(uint32_t a=0; a<ver_num; ++a){
                    for(uint32_t b=0; b<hor_num; ++b){
                        gro::Particle par;
                        par.res_name=gname.mol_name;
                        par.res_num=c+1;
                        par.atom_num=par_count;
                        par.atom_name=gname.atom_name;
                        mv::vec3<double> base={0.0, 0.0, basez};
                        par.pos=base+mv::vec3<double>{xy, 0.0};
                        const double rr12=radius*radius;
                        if(ycount%2==0){
                            if((hole_center.xy()-par.pos.xy()).square()>=rr12){ mom.particles.push_back(par); par.atom_num=++par_count; };
                            xy+=mv::vec2<double>{hor_period*0.5, +ver_step};
                            par.pos=base+mv::vec3<double>{xy, 0.0};
            
    
                            if((hole_center.xy()-par.pos.xy()).square()>=rr12){ mom.particles.push_back(par); par.atom_num=++par_count; };
                            xy+=mv::vec2<double>{hor_period*0.5, -ver_step};
                            par.pos=base+mv::vec3<double>{xy, 0.0};
    
                        }else{
                            if((hole_center.xy()-par.pos.xy()).square()>=rr12){ mom.particles.push_back(par); par.atom_num=++par_count; };
                            xy+=mv::vec2<double>{hor_period*0.5, -ver_step};
                            par.pos=base+mv::vec3<double>{xy, 0.0};
    
                            if((hole_center.xy()-par.pos.xy()).square()>=rr12){ mom.particles.push_back(par); par.atom_num=++par_count; };
                            xy+=mv::vec2<double>{hor_period*0.5, +ver_step};
                            par.pos=base+mv::vec3<double>{xy, 0.0};
    
                        }
                    }
                    if(ycount%2==0) basey+=0.142*2;
                    else            basey+=0.142;
                    xy={0.0f, basey};
                    ++ycount;
                }
                basez+=layer_dist;
            }
        }        
        
    }

    /*
    if(target==Target::GRA){
        
        // Set Auto Graphene Width & Height
        if(!enable_width)  width =gra_layer*4.0;
        if(!enable_height) height=diameter*4.0;
        
        // Constant Values
        const uint32_t hor_num=static_cast<uint32_t>(width/hor_period);
        const double   hor=static_cast<double>(hor_num)*hor_period;
        const uint32_t ver_num=static_cast<uint32_t>(height/ver_period)*2; 
        const double   ver=static_cast<double>(ver_num)*ver_period*0.5;
        const size_t   the_res_num=(cname.mol_name==gname.mol_name ? 1 : 2);

        // Move the CNT coordinate if CNT_CETER = [Auto]
        if(!enable_center && !enable_centerz){
        // Box & CNT Position
        if(enable_center){
            for(size_t a=0; a<mom.num(); ++a) mom.particles[a].pos+=mv::vec3<double>{ center.x, center.y, center.z-length*0.5 };
        
        }else if(enable_centerz){
            for(size_t a=0; a<mom.num(); ++a) mom.particles[a].pos+=mv::vec3<double>{ radius, radius, center.z-length*0.5 };
            center={radius, radius, center.z};
        
        }else{
            for(size_t a=0; a<mom.num(); ++a) mom.particles[a].pos+=mv::vec3<double>{ radius,   radius,   0.0 };
            center={radius, radius, length*0.5};
        }

        if(enable_box){
            mom.box[0]=box;
        
        }else if(enable_boxz){
            mom.box[0]=(box={diameter, diameter, box.z});
        
        }else{
            mom.box[0]=(box={ diameter, diameter, length });

        }

            for(size_t a=0; a<mom.num(); ++a) mom.particles[a].pos+=mv::vec3<double>{ hor*0.5-radius, ver*0.5-radius, 0.0};
            center=mv::vec3<double>{ hor*0.5, ver*0.5, center.z};
            
        }else if(!enable_center &&  enable_centerz){
            
            for(size_t a=0; a<mom.num(); ++a) mom.particles[a].pos+=mv::vec3<double>{ hor*0.5-radius, ver*0.5-radius, 0.0};
            center=mv::vec3<double>{ hor*0.5, ver*0.5, center.z};
        }
        if(!enable_box && !enable_boxz){
            mom.box[0]=(box={ hor, ver, length });
        }else if(!enable_box && enable_boxz){
            mom.box[0]=(box={ hor, ver, box.z });
        }
    

        // Put the Under Carbon Atoms of Graphene
        {
            double basey=0.0;
            mv::vec2<double> xy={0.0, basey};
            uint32_t ycount=0;
            size_t par_count=(graphene_num[0]=mom.num())+1;
            for(uint32_t a=0; a<ver_num; ++a){
                for(uint32_t b=0; b<hor_num; ++b){
                    gro::Particle par;
                    par.res_name=gname.mol_name;
                    par.res_num=the_res_num;
                    par.atom_num=par_count;
                    par.atom_name=gname.atom_name;
                    mv::vec3<double> base={0.0, 0.0, center.z-length*0.5 };
                    par.pos=base+mv::vec3<double>{xy, 0.0};
                    const double rr12=(radius+0.142)*(radius+0.142);
                    if(ycount%2==0){
                        if((center.xy()-par.pos.xy()).square()>=rr12){ mom.particles.push_back(par); par.atom_num=++par_count; };
                        xy+=mv::vec2<double>{hor_period*0.5, +ver_step};
                        par.pos=base+mv::vec3<double>{xy, 0.0};
        

                        if((center.xy()-par.pos.xy()).square()>=rr12){ mom.particles.push_back(par); par.atom_num=++par_count; };
                        xy+=mv::vec2<double>{hor_period*0.5, -ver_step};
                        par.pos=base+mv::vec3<double>{xy, 0.0};

                    }else{
                        if((center.xy()-par.pos.xy()).square()>=rr12){ mom.particles.push_back(par); par.atom_num=++par_count; };
                        xy+=mv::vec2<double>{hor_period*0.5, -ver_step};
                        par.pos=base+mv::vec3<double>{xy, 0.0};

                        if((center.xy()-par.pos.xy()).square()>=rr12){ mom.particles.push_back(par); par.atom_num=++par_count; };
                        xy+=mv::vec2<double>{hor_period*0.5, +ver_step};
                        par.pos=base+mv::vec3<double>{xy, 0.0};

                    }
                }
                if(ycount%2==0) basey+=0.142*2;
                else            basey+=0.142;
                xy={0.0f, basey};
                ++ycount;
            }
        }
        mom.num()=mom.particles.size();
        

        // Put the Upper Carbon Atoms of Graphene
        {
            double basey=0.0;
            mv::vec2<double> xy={0.0, basey};
            uint32_t ycount=0;
            size_t par_count=(graphene_num[1]=mom.num())+1;
            for(uint32_t a=0; a<ver_num; ++a){
                for(uint32_t b=0; b<hor_num; ++b){
                    gro::Particle par;
                    par.res_name=gname.mol_name;
                    par.res_num=(the_res_num==2 ? 3 : 1);
                    par.atom_num=par_count;
                    par.atom_name=gname.atom_name;
                    mv::vec3<double> base={0.0, 0.0, center.z+length*0.5 };
                    par.pos=base+mv::vec3<double>{xy, 0.0};
                    const double rr12=(radius+0.142)*(radius+0.142);
                    if(ycount%2==0){
                        if((center.xy()-par.pos.xy()).square()>=rr12){ mom.particles.push_back(par); par.atom_num=++par_count; };
                        xy+=mv::vec2<double>{hor_period*0.5, +ver_step};
                        par.pos=base+mv::vec3<double>{xy, 0.0};

                        if((center.xy()-par.pos.xy()).square()>=rr12){ mom.particles.push_back(par); par.atom_num=++par_count; };
                        xy+=mv::vec2<double>{hor_period*0.5, -ver_step};
                        par.pos=base+mv::vec3<double>{xy, 0.0};

                    }else{
                        if((center.xy()-par.pos.xy()).square()>=rr12){ mom.particles.push_back(par); par.atom_num=++par_count; };
                        xy+=mv::vec2<double>{hor_period*0.5, -ver_step};
                        par.pos=base+mv::vec3<double>{xy, 0.0};

                        if((center.xy()-par.pos.xy()).square()>=rr12){ mom.particles.push_back(par); par.atom_num=++par_count; };
                        xy+=mv::vec2<double>{hor_period*0.5, +ver_step};
                        par.pos=base+mv::vec3<double>{xy, 0.0};

                    }
                }
                if(ycount%2==0) basey+=0.142*2;
                else            basey+=0.142;
                xy={0.0f, basey};
                ++ycount;
            }
        }
        if(!enable_box && !enable_boxz) mom.box[0]={hor, ver, length};
        if(!enable_box &&  enable_boxz) mom.box[0]={hor, ver, box.z};
    }
   


    //++++++++++++++++++++++++++++++++++++++++//
    //    Calculation of Graphene Position    //
    //++++++++++++++++++++++++++++++++++++++++//
    if(!enable_info) std::cerr<<"(2) Calculating Graphene Position"<<std::endl;
    
    size_t   graphene_num[2]={0, 0};
    if(target==Target::CNTGRA){
        
        // Set Auto Graphene Width & Height
        if(!enable_width)  width =diameter*4.0;
        if(!enable_height) height=diameter*4.0;
        
        // Constant Values
        const uint32_t hor_num=static_cast<uint32_t>(width/hor_period);
        const double   hor=static_cast<double>(hor_num)*hor_period;
        const uint32_t ver_num=static_cast<uint32_t>(height/ver_period)*2; 
        const double   ver=static_cast<double>(ver_num)*ver_period*0.5;
        const size_t   the_res_num=(cname.mol_name==gname.mol_name ? 1 : 2);

        // Move the CNT coordinate if CNT_CETER = [Auto]
        if(!enable_center && !enable_centerz){

            for(size_t a=0; a<mom.num(); ++a) mom.particles[a].pos+=mv::vec3<double>{ hor*0.5-radius, ver*0.5-radius, 0.0};
            center=mv::vec3<double>{ hor*0.5, ver*0.5, center.z};
            
        }else if(!enable_center &&  enable_centerz){
            
            for(size_t a=0; a<mom.num(); ++a) mom.particles[a].pos+=mv::vec3<double>{ hor*0.5-radius, ver*0.5-radius, 0.0};
            center=mv::vec3<double>{ hor*0.5, ver*0.5, center.z};
        }
        if(!enable_box && !enable_boxz){
            mom.box[0]=(box={ hor, ver, length });
        }else if(!enable_box && enable_boxz){
            mom.box[0]=(box={ hor, ver, box.z });
        }
    

        // Put the Under Carbon Atoms of Graphene
        {
            double basey=0.0;
            mv::vec2<double> xy={0.0, basey};
            uint32_t ycount=0;
            size_t par_count=(graphene_num[0]=mom.num())+1;
            for(uint32_t a=0; a<ver_num; ++a){
                for(uint32_t b=0; b<hor_num; ++b){
                    gro::Particle par;
                    par.res_name=gname.mol_name;
                    par.res_num=the_res_num;
                    par.atom_num=par_count;
                    par.atom_name=gname.atom_name;
                    mv::vec3<double> base={0.0, 0.0, center.z-length*0.5 };
                    par.pos=base+mv::vec3<double>{xy, 0.0};
                    const double rr12=(radius+0.142)*(radius+0.142);
                    if(ycount%2==0){
                        if((center.xy()-par.pos.xy()).square()>=rr12){ mom.particles.push_back(par); par.atom_num=++par_count; };
                        xy+=mv::vec2<double>{hor_period*0.5, +ver_step};
                        par.pos=base+mv::vec3<double>{xy, 0.0};
        

                        if((center.xy()-par.pos.xy()).square()>=rr12){ mom.particles.push_back(par); par.atom_num=++par_count; };
                        xy+=mv::vec2<double>{hor_period*0.5, -ver_step};
                        par.pos=base+mv::vec3<double>{xy, 0.0};

                    }else{
                        if((center.xy()-par.pos.xy()).square()>=rr12){ mom.particles.push_back(par); par.atom_num=++par_count; };
                        xy+=mv::vec2<double>{hor_period*0.5, -ver_step};
                        par.pos=base+mv::vec3<double>{xy, 0.0};

                        if((center.xy()-par.pos.xy()).square()>=rr12){ mom.particles.push_back(par); par.atom_num=++par_count; };
                        xy+=mv::vec2<double>{hor_period*0.5, +ver_step};
                        par.pos=base+mv::vec3<double>{xy, 0.0};

                    }
                }
                if(ycount%2==0) basey+=0.142*2;
                else            basey+=0.142;
                xy={0.0f, basey};
                ++ycount;
            }
        }
        mom.num()=mom.particles.size();
        

        // Put the Upper Carbon Atoms of Graphene
        {
            double basey=0.0;
            mv::vec2<double> xy={0.0, basey};
            uint32_t ycount=0;
            size_t par_count=(graphene_num[1]=mom.num())+1;
            for(uint32_t a=0; a<ver_num; ++a){
                for(uint32_t b=0; b<hor_num; ++b){
                    gro::Particle par;
                    par.res_name=gname.mol_name;
                    par.res_num=(the_res_num==2 ? 3 : 1);
                    par.atom_num=par_count;
                    par.atom_name=gname.atom_name;
                    mv::vec3<double> base={0.0, 0.0, center.z+length*0.5 };
                    par.pos=base+mv::vec3<double>{xy, 0.0};
                    const double rr12=(radius+0.142)*(radius+0.142);
                    if(ycount%2==0){
                        if((center.xy()-par.pos.xy()).square()>=rr12){ mom.particles.push_back(par); par.atom_num=++par_count; };
                        xy+=mv::vec2<double>{hor_period*0.5, +ver_step};
                        par.pos=base+mv::vec3<double>{xy, 0.0};

                        if((center.xy()-par.pos.xy()).square()>=rr12){ mom.particles.push_back(par); par.atom_num=++par_count; };
                        xy+=mv::vec2<double>{hor_period*0.5, -ver_step};
                        par.pos=base+mv::vec3<double>{xy, 0.0};

                    }else{
                        if((center.xy()-par.pos.xy()).square()>=rr12){ mom.particles.push_back(par); par.atom_num=++par_count; };
                        xy+=mv::vec2<double>{hor_period*0.5, -ver_step};
                        par.pos=base+mv::vec3<double>{xy, 0.0};

                        if((center.xy()-par.pos.xy()).square()>=rr12){ mom.particles.push_back(par); par.atom_num=++par_count; };
                        xy+=mv::vec2<double>{hor_period*0.5, +ver_step};
                        par.pos=base+mv::vec3<double>{xy, 0.0};

                    }
                }
                if(ycount%2==0) basey+=0.142*2;
                else            basey+=0.142;
                xy={0.0f, basey};
                ++ycount;
            }
        }
        if(!enable_box && !enable_boxz) mom.box[0]={hor, ver, length};
        if(!enable_box &&  enable_boxz) mom.box[0]={hor, ver, box.z};
    }









    */
    //++++++++++++++++//
    //     Writing    //
    //++++++++++++++++//
    mom.title="Generated by mkcg";
    std::cout<<"Par:"<<mom.num()<<" "<<mom.particles.size()<<std::endl;
    std::cout<<"Box:"<<mom.box[0]<<std::endl;

    gro::File sub(output+".gro", std::ios::out);
    sub.moments.push_back(mom);
    //std::cout<<"Box:"<<sub.moments[0].box[0]<<std::endl;
    /*for(uint32_t a=0; a<mom.num(); ++a){
        std::cout<<a<<" "<<mom.num()<<std::endl;
        std::cout<<"Box:"<<sub.moments[0].box[0]<<std::endl;
        std::cout<<sub.moments[0].particles[a].str()<<std::endl;
    }*/
    sub.write(); 
 
    

    //+++++++++++++++++++++++//
    //    Making Topology    //
    //+++++++++++++++++++++++//
    if(!enable_info) std::cerr<<"(3) Making Topology"<<std::endl;
    
    std::ofstream itp(output+".itp", std::ios::out);

    // Moleculetype
    itp<<"[ moleculetype ]"<<std::endl;
    itp<<"; Name                         nrexcl"<<std::endl;
    switch(target){
        case Target::CNT:
            itp<<"  CNT    "<<nrexcl<<std::endl;
            break;
        case Target::CNTGRA:
            itp<<"  CNTGRA "<<nrexcl<<std::endl;
            break;
        case Target::GRA:
            itp<<"  GRA    "<<nrexcl<<std::endl;
            break;
    }
    itp<<std::endl;

    // Atoms
    itp<<"[ atoms ]"<<std::endl;
    itp<<"; num  type resnr resid  atom  cgnr   charge      mass"<<std::endl;
    switch(target){
        case Target::CNT:
        {
            for(size_t a=0; a<mom.num(); ++a){
                gro::Particle& par=mom.particles[a];
                std::string sub=par.atom_name.substr(0, 2);
                
                char line[56]={'\0'};
                if(a==0) itp<<"; residue 1  CNT"<<std::endl;
                std::sprintf(line, "%5u %5s %5u %5s %5s %5u %1s%7.5f %9.5f", static_cast<uint32_t>(par.atom_num), par.atom_name.c_str(), static_cast<uint32_t>(par.res_num), par.res_name.c_str(), par.atom_name.c_str(), static_cast<uint32_t>(par.atom_num), (sub=="CP" ? "+" : (sub=="CM" ? "-" : " ")), (sub=="CP" || sub=="CM") ? charge.amount : 0.0 , 12.01100);
                itp<<line<<std::endl;

            }
            break;
        }
        case Target::CNTGRA:
        {
            for(size_t a=0; a<mom.num(); ++a){
                gro::Particle& par=mom.particles[a];
                std::string sub=par.atom_name.substr(0, 2);
                
                char line[56]={'\0'};
                if(a==0)              itp<<"; residue 1  CNT"<<std::endl;
                if(a==resid_separ[0]) itp<<"; residue 2  Lower Graphene"<<std::endl;
                if(a==resid_separ[1]) itp<<"; residue 3  Upper Graphene"<<std::endl;
                std::sprintf(line, "%5u %5s %5u %5s %5s %5u %1s%7.5f %9.5f", static_cast<uint32_t>(par.atom_num), par.atom_name.c_str(), static_cast<uint32_t>(par.res_num), par.res_name.c_str(), par.atom_name.c_str(), static_cast<uint32_t>(par.atom_num), (sub=="CP" ? "+" : (sub=="CM" ? "-" : " ")), (sub=="CP" || sub=="CM") ? charge.amount : 0.0 , 12.01100);
                itp<<line<<std::endl;

            }
            break;
        }
        case Target::GRA:
        {
            resid_separ.push_back(~static_cast<size_t>(0));
            uint32_t resid_separ_counter=0;
            for(size_t a=0; a<mom.num(); ++a){
                gro::Particle& par=mom.particles[a];
                std::string sub=par.atom_name.substr(0, 2);
                
                char line[56]={'\0'};
                if(a==resid_separ[resid_separ_counter]){
                    ++resid_separ_counter;
                    itp<<"; residue "<<resid_separ_counter<<"  Graphene of "<<resid_separ_counter<<"'s Layer"<<std::endl;
                }

                std::sprintf(line, "%5u %5s %5u %5s %5s %5u %1s%7.5f %9.5f", static_cast<uint32_t>(par.atom_num), par.atom_name.c_str(), static_cast<uint32_t>(par.res_num), par.res_name.c_str(), par.atom_name.c_str(), static_cast<uint32_t>(par.atom_num), (sub=="CP" ? "+" : (sub=="CM" ? "-" : " ")), (sub=="CP" || sub=="CM") ? charge.amount : 0.0 , 12.01100);
                itp<<line<<std::endl;
            }
            break;
        }
    }
    itp<<std::endl;
    

    // Bonds, Angles and Torsions
    // Bonds
    struct Bond{ size_t fir; size_t sec; };
    std::vector<Bond> bonds;
    if(nrexcl>0){

        // Calculate
        std::vector<uint16_t> count(mom.num());  for(size_t a=0; a<count.size(); ++a) count[a]=0;
        for(size_t a=0; a<mom.num(); ++a){
                
            gro::Particle& para=mom.particles[a];
            for(size_t b=a+1; b<mom.num(); ++b){
                constexpr double bleng=(0.142*1.5)*(0.142*1.5);
                gro::Particle& parb=mom.particles[b];
                mv::vec3<double> dist=para.pos-parb.pos;
                if(target==Target::CNTGRA or target==Target::GRA){
                    mv::vec3<double> halbox=mom.box[0]*0.5;
                    if     (dist.x > halbox.x) dist.x-=mom.box[0].x;
                    else if(dist.x<=-halbox.x) dist.x+=mom.box[0].x;
                    if     (dist.y > halbox.y) dist.y-=mom.box[0].y;
                    else if(dist.y<=-halbox.y) dist.y+=mom.box[0].y;
                    if     (dist.z > halbox.z) dist.z-=mom.box[0].z;
                    else if(dist.z<=-halbox.z) dist.z+=mom.box[0].z;
                }

                if(para.res_num==parb.res_num && dist.square()<bleng &&
                    count[a]<3                && count[b]<3    
                ){
                    bonds.push_back({para.atom_num, parb.atom_num});
                    ++count[a];
                    ++count[b];
                }
            }
        }

        // Bond Output
        itp<<"[ bonds ]"<<std::endl;
        for(size_t a=0; a<bonds.size(); ++a){
            char line[12]={'0'};
            std::sprintf(line, "%5u %5u", static_cast<uint32_t>(bonds[a].fir), static_cast<uint32_t>(bonds[a].sec));
            itp<<line<<std::endl;
    
        }
        itp<<std::endl;
    }


    // Angles
    struct Angle{ size_t fir; size_t sec; size_t thi; };
    std::vector<Angle> angles;
    if(nrexcl>1){

        // Calculate
        for(size_t a=0; a<bonds.size(); ++a){
            size_t nr=a+1;

            for(size_t b=0; b<bonds.size(); ++b){
                size_t b_fir=bonds[b].fir;
                size_t b_sec=bonds[b].sec;
                
                if(nr==b_fir){
                    
                    for(size_t c=b+1; c<bonds.size(); ++c){
                        size_t c_fir=bonds[c].fir;
                        size_t c_sec=bonds[c].sec;
                    
                        if(c_fir==b_sec){
                            angles.push_back({b_fir, b_sec, c_sec});
                        
                        }
                        else if(c_sec==b_sec){
                            angles.push_back({b_fir, b_sec, c_fir});
                    
                        }
                    }
                }
                else if(nr==b_sec){
                
                    for(size_t c=b+1; c<bonds.size(); ++c){
                        size_t c_fir=bonds[c].fir;
                        size_t c_sec=bonds[c].sec;
                    
                        if(c_fir==b_fir){
                            angles.push_back({b_sec, c_fir, c_sec});

                        }
                        else if(c_sec==b_fir){
                            angles.push_back({b_sec, b_fir, c_fir});
                    
                        }
                    }
                }
            }
        }


        // Angle Output 
        itp<<"[ angles ]"<<std::endl;
        for(size_t a=0; a<angles.size(); ++a){
            Angle& ag=angles[a];
            char line[18]={'0'};
            std::sprintf(line, "%5u %5u %5u", static_cast<uint32_t>(ag.fir), static_cast<uint32_t>(ag.sec), static_cast<uint32_t>(ag.thi));
            itp<<line<<std::endl;
    
        }
        itp<<std::endl; 
    }


    // Torsions
    struct Torsion{ size_t fir; size_t sec; size_t thi; size_t fot; };
    std::vector<Torsion> torsions;
    if(nrexcl>2){
        
        // Calculate
        for(size_t a=0; a<angles.size(); ++a){
            size_t a_fir=angles[a].fir;
            size_t a_sec=angles[a].sec;
            size_t a_thi=angles[a].thi;

            for(size_t b=0; b<angles.size(); ++b){
                size_t b_fir=angles[b].fir;
                size_t b_sec=angles[b].sec;
                size_t b_thi=angles[b].thi;

                if     (a_sec==b_fir && a_thi==b_sec && a_fir<b_thi){
                    torsions.push_back({a_fir, a_sec, a_thi, b_thi});
                }
                if(a_sec==b_thi && a_thi==b_sec && a_fir<b_fir){
                    torsions.push_back({a_fir, a_sec, a_thi, b_fir});
                }
                if(a_fir==b_sec && a_sec==b_fir && b_thi<a_thi){
                    torsions.push_back({b_thi, b_sec, b_fir, a_thi});
                }
                if(a_thi==b_sec && a_sec==b_fir && b_thi<a_fir){
                    torsions.push_back({a_fir, b_fir, b_sec, b_thi});
                }

            }
        }

        // Torsion Output
        {
            itp<<"[ torsions ]"<<std::endl;
            for(size_t a=0; a<torsions.size(); ++a){
                Torsion& tr=torsions[a];
                char line[24]={'0'};
                std::sprintf(line, "%5u %5u %5u %5u", static_cast<uint32_t>(tr.fir), static_cast<uint32_t>(tr.sec), static_cast<uint32_t>(tr.thi), static_cast<uint32_t>(tr.fot));
                itp<<line<<std::endl;
        
            }
            itp<<std::endl; 
        }
    }
    
    /*
    if(enable_info){
        std::cerr<<"File String                   : "<<output<<std::endl;
        std::cerr<<"CNT Length              [nm]  : "<<length<<std::endl;
        std::cerr<<"CNT Diameter            [nm]  : "<<diameter<<std::endl;
        std::cerr<<"CNT Chiral             [1,1]  : "<<chiral[1]<<","<<chiral[0]<<std::endl;
        std::cerr<<"Charge Amount & Number [e,1]  : "<<charge.amount<<","<<charge.number<<std::endl;
        std::cerr<<"Number of CNT Atoms      [1]  : "<<graphene_num[0]<<std::endl;
        if(enable_graph){
            std::cerr<<"Graphene Wall                 : On"<<std::endl;
            std::cerr<<"Graphene Width          [nm]  : "<<width<<std::endl;
            std::cerr<<"Graphene Height         [nm]  : "<<height<<std::endl;
            std::cerr<<"Number of CNT Graphene   [1]  : "<<(graphene_num[1]-graphene_num[0])*2<<std::endl;
        }
        std::cerr<<"Box                     [nm]  : "<<box<<std::endl;
        std::cerr<<"CNT Center              [nm]  : "<<center<<std::endl;
    }
    else std::cerr<<"(4) Terminated"<<std::endl;
    */

    return 0;
}
