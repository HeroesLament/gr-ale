// modem.hpp

#ifndef MODEM_HPP

#define MODEM_HPP
#define SAMPLE_BUFFER_SIZE 4096
#define FFT_SIZE 2048

class Modem {
    public:
        enum class PREAMBLE_TYPE {
            DATA, THRU, TO, TWS, FROM, TIS, CMD, REP, NONE
        };

        enum class MODEM_STATE {
            IDLE,
            SCANNING,
            SOUNDING,
            EXCHANGE,
            LINKING,
            LINKED,
            RECEIVING_PREAMBLE,
            RECEIVING_DATA,
            SENDING_PREAMBLE,
            SENDING_DATA
        };

        enum class MODEM_RETURNS {
            SUCCESS = 0,
            INVALID_LENGTH = -1,
            NULL_POINTER = -2,
            SAMPLE_GATHER_FAILURE = -3,
            CARRIER_TONE_DETECTION_ERROR = -4,
            SYNC_FAILURE = -5,
            INVALID_SYMBOL = -6
        };

        struct SYNC_RESULTS {
            MODEM_RETURNS resultCode;
            PREAMBLE_TYPE preambleType;
        };
    private:
        float sampleBuffer[SAMPLE_BUFFER_SIZE];
        int ito2, itws2, ifrom2, itis2, irep2, idata2;
        int currentSamplePosition = 0;  // Current position in sampleBuffer
        int fft_history_offset;
        std::complex<double> fft_out[FFT_SIZE];
        double fft_history[FFT_SIZE];
        double fft_cs_twiddle[FFT_SIZE / 2];
        double fft_ss_twiddle[FFT_SIZE / 2];
        double fft_mag[FFT_SIZE / 2];
        MODEM_STATE currentState;
        MODEM_STATE previousState;
        static const unsigned int encode_table[];
        static const unsigned int error_table[];
    public:
        Modem();  // constructor
        ~Modem(); // destructor
        void resetHistory();
        void computeTwiddles();
        bool internalGather(float *buffer, int size);
        MODEM_RETURNS processFFT(float *sample, int length);
        MODEM_RETURNS gatherSample(float *sampleBuffer, int bufferSize);
        MODEM_RETURNS detectCarrierTone(float *sample, int length);
        MODEM_RETURNS modulateMFSK(int symbol, float* outputBuffer, int bufferSize);
        MODEM_RETURNS demodulateMFSK(float *sampleBuffer, int bufferSize, int *outputSymbols, int &numSymbols);
        SYNC_RESULTS synchronize(float* sample, int length);
        // PREAMBLE_TYPE decode(int symbol);
        // int encode(PREAMBLE_TYPE preamble);
        unsigned long golay_encode(unsigned int data);
        unsigned int golay_decode(unsigned long code, int &errors);
        unsigned long modem_de_interleave_and_fec(int *input, int *errors);
        void modem_new_symbol(int sym, int nr);
};

#endif // MODEM_HPP