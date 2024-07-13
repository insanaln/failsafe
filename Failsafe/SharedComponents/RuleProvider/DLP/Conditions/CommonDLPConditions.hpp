#pragma once

#include <regex>

#include "SharedComponents/RuleProvider/DLP/Conditions/IDLPConditions.hpp"

#include "nlohmann/json.hpp"

class CommonDLPConditions : public IDLPConditions {
public:
    CommonDLPConditions( const nlohmann::json &j );

    virtual bool CheckConditions( const DLPOperation &operation ) override;
   
   /*
    // New method to check allowed applications
    bool isApplicationAllowed(const std::string& applicationPath) const; */

private:
    std::optional< std::string > fileExtension_;
    std::optional< std::string > pathPrefix_;
    std::optional< std::regex > pathRegex_;
    //std::optional<std::vector<std::string>> allowedApplications_;

};