#include <iostream>
#include <string>
#include <memory>
#include <ctime>



using namespace std;

class CloudStorage
{
public:
    virtual bool uploadContents(const string& content) = 0;
    virtual int getFreeSpace() = 0;
    virtual ~CloudStorage() = default;
};

class CloudDrive : public CloudStorage
{
public:
    bool uploadContents(const string& content) override
    {
        cout << "Uploading " << content.length() << " bytes to CloudDrive: " << endl;

        return true;
    }

    int getFreeSpace() override
    {
        // Implement the logic for getting the free space on CloudDrive here.
        const int size = arc4random_uniform(20);
        cout << "Available CloudDrive storage: " << size << "GB" << endl;
        return size;
    }
};

class FastShare : public CloudStorage
{
public:
    bool uploadContents(const string& content) override
    {
        cout << "Uploading " << content.length() << " bytes to FastShare: " << endl;
        return true;
    }

    int getFreeSpace() override
    {
        const int size = arc4random_uniform(10);
        cout << "Available FastShare storage: " << size << "GB" << endl;
        return size;
    }
};

// 3rd party service
class VirtualDrive
{
public:
    bool uploadData(const string& data, const int uniqueID)
    {
        cout << "Uploading to VirtualDrive: \"" << data << "\" ID: " << uniqueID << endl;
        return true;
    }
    int usedSpace()
    {
        return arc4random_uniform(10);
    }
    const int totalSpace = 15;
};


class VirtualDriveAdapter : public CloudStorage, private VirtualDrive
{

public:
    bool uploadContents(const string& content) override
    {
        int unique_ID=generateUID();
        cout << "Uploading " << content.length() << " bytes to VirtualDrive: " << endl;
        return uploadData(content,unique_ID);
    }

    int getFreeSpace() override
    {
        // Implement the logic for getting the free space on CloudDrive here.
        const int size = totalSpace - usedSpace();
        cout << "Available VirtualDrive storage: " << size << "GB" << endl;
        return size;
    }

private:
    // generates an ID from seconds passed since Epoch
    int generateUID()
    {
        // seconds since the Epoch
        const time_t result = time(nullptr);        
        return result;
    }

};


int main()
{
    // Create an array of pointers to CloudStorage objects.
    const std::unique_ptr<CloudStorage> cloudServices[]
    {
        std::make_unique<CloudDrive>(),
        std::make_unique<FastShare>(),
        std::make_unique<VirtualDriveAdapter>(),
    };

    // Iterate through the array and invoke the uploadContents and getFreeSpace
    // methods on each object.
    const string content = "Beam me up, Scotty!";
    for (const auto &service : cloudServices)
    {        
        service->uploadContents(content);
        service->getFreeSpace();
        cout << endl;
    }

    return 0;
}
