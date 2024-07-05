#pragma once

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <memory>

#include "Modules/DLP/FSMessages/FSMessage.hpp"
#include "SharedComponents/RuleProvider/DLP/DLPOperationType.hpp"

class DLPOperation {
public:
    virtual ~DLPOperation() = default;

    DLPOperationType Operation() const
    {
        return operation_;
    }

    void Allow()
    {
        controlMessage_->AllowOp();
    }

    void Block()
    {
        controlMessage_->BlockOp();
    }

    uid_t UserId() const
    {
        return controlMessage_->Uid();
    }

    std::chrono::system_clock::time_point TimePoint() const
    {
        return controlMessage_->TimePoint();
    }

    std::string_view ExecutablePath() const
    {
        return controlMessage_->ExecutablePath();
    }

    std::string ToString() const
    {
        return controlMessage_->ToString();
    }


    // Method to get the application path on an Ubuntu system
    std::string ApplicationPath(const std::string& applicationName) const {
        std::string command = "which " + applicationName + " > /tmp/app_path.txt";
        int result = std::system(command.c_str());

        if (result != 0) {
            std::cerr << "Failed to execute command to find application path" << std::endl;
            return "";
        }

        std::ifstream file("/tmp/app_path.txt");
        std::string path;
        if (file.is_open()) {
            std::getline(file, path);
            file.close();
        }

        std::remove("/tmp/app_path.txt");
        return path;
    }

    std::string getApplicationPath() const {
        // Implement based on your application's logic
        // For example, return ApplicationPath(applicationName);
        std::string applicationName = this->applicationName; // You need to have this member or a way to get it
        return ApplicationPath(applicationName);
    }    
    
protected:
    DLPOperation( DLPOperationType operation, std::shared_ptr< FSMessage > controlMessage )
        : operation_( operation ),
          controlMessage_( std::move( controlMessage ) )
    {
    }

    DLPOperationType operation_;
    std::shared_ptr< FSMessage > controlMessage_;
};