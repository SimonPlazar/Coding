#ifndef SIMONPLAZAR0401_ARTIST_H
#define SIMONPLAZAR0401_ARTIST_H

#include <string>
#include "Date.h"

class Artist {
protected:
    std::string name;
    std::string biography;
    Date dateOfBirth;
public:
    Artist();

    Artist(std::string name, std::string biography, Date dateOfBirth);

    const std::string &getName() const;

    const std::string &getBiography() const;

    Date getDateOfBirth() const;

    void setName(const std::string &x);

    void setBiography(const std::string &x);

    void setDateOfBirth(Date x);

    virtual std::string toString() const;
};


#endif //SIMONPLAZAR0401_ARTIST_H
