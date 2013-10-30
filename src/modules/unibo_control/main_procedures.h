/*
 *
 * Filename: main_procedures.h
 * Authors: Paolo Di Febbo, Luca De Luigi.
 *
 * Description:
 * Header file delle procedure utilizzate nel main
 *
 */

// Funzione lettura seriale (usata solo per xbee)
// legge dalla seriale e mette dentro "frame" il contenuto
void readAndParseSerial(int serial_port, char* buff, int bsize, char* frame, int* p, int* s, int* lsi, bool* packet_ready);

// utile per eventuale benchmark, ritorna il tempo gettimeofday in usec
unsigned long int getMyTime();

// due funzioni utilizzate nell'inzializzazione
void flush_serial(int serial_port);
void flush_udp(int udp_port);

// handler per resettare le opzioni delle porte seriali
void cleanup_termios(int signal);

// riempie il pacchetto mavlink SERVO_OUTPUT_RAW con i valori ottenuti da cinputs, scalati correttamente in micros pwm
//void scale_cinputs_to_px4pwm(mavlink_servo_output_raw_t* px4_output, CInputs & cinputs);
//void scale_cinputs_to_px4pwm(mavlink_servo_output_raw_t* px4_output, cInputs_s* cinputs);

// funzione di inizializzazione generale (molto lunga)
void init(int argc, char* argv[]);
