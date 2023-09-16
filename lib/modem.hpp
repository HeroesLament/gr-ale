// modem.hpp

#ifndef MODEM_HPP
#define MODEM_HPP

class Modem {
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
        unsigned long encode(unsigned int data);
        unsigned int decode(unsigned long code, int &errors);
};

#endif // MODEM_HPP