// modem.hpp

#ifndef MODEM_HPP

#define MODEM_HPP
#define SAMPLE_BUFFER_SIZE 4096
#define FFT_SIZE 2048

namespace ale {
    namespace modem {
        const int NR = 10; 
        const int ANOTHER_DIMENSION = 5; 
        static const int VOTE_ARRAY_LENGTH = 10; // Replace 10 with the actual value you want to assign
        static const int SYMBOLS_PER_WORD = 5; // Replace 5 with the actual value you want to assign
        int ber[48];

        class Modem {
            // Public enum class definitions
            public:
                enum SYNC_STATES {
                    NOT_WORD_SYNC = 0, // replace with actual value
                    WORD_SYNC = 1 // replace with actual value
                };

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

                static constexpr int BAD_VOTE_THRESHOLD = 4; // replace with actual value
                static constexpr int SYNC_ERROR_THRESHOLD = 100; // replace with actual value
            
            // Internally-accessible variables
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
                const int VOTE_BUFFER_LENGTH = 48;
                int nr[NR][ANOTHER_DIMENSION]; // This declares a 2D array named nr with dimensions NR x ANOTHER_DIMENSION
                int inew;
                static const int Dimension1 = 10; // Assuming it has 10 elements in first dimension
                static const int Dimension2 = 5; // Assuming each element has 5 in the second dimension
                int bits[Dimension1][Dimension2];
                int word_sync_position[Dimension2];
                int input_buffer_pos[Dimension2];
                static const int vote_lookup[Dimension2];
                int word_sync[Dimension2];

            // Externally-accessible methods
            public:
                Modem();  // constructor
                ~Modem(); // destructor
                void processData(float* data, int size);

                //Internally-accessible methods
                private:
                    void resetHistory();
                    void computeTwiddles();
                    void transitionTo(MODEM_STATE newState);
                    MODEM_RETURNS gatherSample(float *sampleBuffer, int bufferSize);
                    MODEM_RETURNS detectCarrierTone(float *sample, int length);
                    MODEM_RETURNS processFFT(float *sample, int length);
                    MODEM_RETURNS demodulateMFSK(float *sampleBuffer, int bufferSize, int *outputSymbols, int &numSymbols);
                    MODEM_RETURNS modulateMFSK(int symbol, float* outputBuffer, int bufferSize);
                    unsigned int golay_encode(unsigned int data);
                    unsigned int golay_decode(unsigned int code, unsigned int errors);
                    unsigned int modem_de_interleave_and_fec(int *input, int *errors);
                    void modem_new_symbol(int sym, int nr);
                    void decode_word(int word, int nr, int bad_votes);
                    // int encode(PREAMBLE_TYPE preamble);
                    // PREAMBLE_TYPE decode(int symbol);
                    bool internalGather(float *buffer, int size);
                    SYNC_RESULTS synchronize(float* sample, int length);

        };
    }
}
#endif // MODEM_HPP