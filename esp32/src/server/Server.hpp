#ifndef SERVER_H
#define SERVER_H

typedef struct {
    uint32_t jumps;
} training_sample_t;

class Server {
    private:
        const String SERVER_NAME;
    public:
        Server(String& serverName);
        void startTraining();
        void sendData();
};

#endif