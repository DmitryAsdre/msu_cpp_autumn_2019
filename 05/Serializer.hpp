#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP
#include <iostream>
#include <string.h>
#include <sstream>
#include <stdlib.h>
struct Data
{
    uint64_t a;
    bool b;
    uint64_t c;

    template <class Serializer>
    void serialize(Serializer& serializer)
    {
        serializer(a, b, c);
    }
    template <class Deserializer>
    void deserialize(Deserializer& deserializer)
    {
        deserializer(a, b, c);
    }
};
class Serializer
{
    private:
        static constexpr char Separator = ' ';
        std::ostream& out;
    public:
        explicit Serializer(std::ostream& out_):
            out(out_)
        {}

        template <class T>
        void save(T& obj)
        {
            obj.serialize(*this);
        }

        template <class... ArgsT>
        void operator()(ArgsT&&... args)
        {
            process(std::forward<ArgsT>(args)...);
        }
    private:
        template <class ArgT>
        void process(ArgT&& val)
        {
            print(val);
        }

        template <class ArgT, class... Args>
        void process(ArgT&& val, Args&&... args)
        {
            process(val);
            process(std::forward<Args>(args)...);
        }

        void print(uint64_t val)
        {
            out << val << Separator;
        }
        void print(bool val)
        {
            val ? out << "true" << Separator : out << "false" << Separator;
        }
};
class Deserializer
{
    private:
        static constexpr char Separator = ' ';
        std::istream& in;
    public:
        explicit Deserializer(std::istream& in_):
            in(in_)
        {}
        
        template <class T>
        void load(T& obj)
        {
             obj.deserialize(*this);
        }

        template <class... ArgsT>
        void operator()(ArgsT&&... args)
        {
            process(std::forward<ArgsT>(args)...);
        }
    private:
    
        template<class ArgT>
        void process(ArgT&& val)
        {
            read(val);
        }

        template<class ArgT, class... Args>
        void process(ArgT&& val, Args&&... args)
        {
            process(val);
            process(std::forward<Args>(args)...);
        }

        void read(uint64_t& val)
        {
            in >> val;
        }
        void read(bool& val)
        {
            std::string str;
            in >> str;
            if(str == "true")
                val = true;
            else if(str == "false")
                val = false;
            else 
                throw std::runtime_error("no str");
        }

};
#endif