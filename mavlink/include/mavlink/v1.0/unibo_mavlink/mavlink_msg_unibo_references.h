// MESSAGE UNIBO_REFERENCES PACKING

#define MAVLINK_MSG_ID_UNIBO_REFERENCES 202

typedef struct __mavlink_unibo_references_t
{
 uint64_t Tstamp; ///< 
 float p_refX; ///< 
 float p_refY; ///< 
 float p_refZ; ///< 
 float dot_p_refX; ///< 
 float dot_p_refY; ///< 
 float dot_p_refZ; ///< 
 float dot2_p_refX; ///< 
 float dot2_p_refY; ///< 
 float dot2_p_refZ; ///< 
 float dot3_p_refX; ///< 
 float dot3_p_refY; ///< 
 float dot3_p_refZ; ///< 
 float dot4_p_refX; ///< 
 float dot4_p_refY; ///< 
 float dot4_p_refZ; ///< 
 float psi_ref; ///< 
 float dot_psi_ref; ///< 
 float dot2_psi_ref; ///< 
 float Thrust; ///< 
 float q0; ///< 
 float q1; ///< 
 float q2; ///< 
 float q3; ///< 
 uint32_t buttons; ///< 
} mavlink_unibo_references_t;

#define MAVLINK_MSG_ID_UNIBO_REFERENCES_LEN 104
#define MAVLINK_MSG_ID_202_LEN 104

#define MAVLINK_MSG_ID_UNIBO_REFERENCES_CRC 150
#define MAVLINK_MSG_ID_202_CRC 150



#define MAVLINK_MESSAGE_INFO_UNIBO_REFERENCES { \
	"UNIBO_REFERENCES", \
	25, \
	{  { "Tstamp", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_unibo_references_t, Tstamp) }, \
         { "p_refX", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_unibo_references_t, p_refX) }, \
         { "p_refY", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_unibo_references_t, p_refY) }, \
         { "p_refZ", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_unibo_references_t, p_refZ) }, \
         { "dot_p_refX", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_unibo_references_t, dot_p_refX) }, \
         { "dot_p_refY", NULL, MAVLINK_TYPE_FLOAT, 0, 24, offsetof(mavlink_unibo_references_t, dot_p_refY) }, \
         { "dot_p_refZ", NULL, MAVLINK_TYPE_FLOAT, 0, 28, offsetof(mavlink_unibo_references_t, dot_p_refZ) }, \
         { "dot2_p_refX", NULL, MAVLINK_TYPE_FLOAT, 0, 32, offsetof(mavlink_unibo_references_t, dot2_p_refX) }, \
         { "dot2_p_refY", NULL, MAVLINK_TYPE_FLOAT, 0, 36, offsetof(mavlink_unibo_references_t, dot2_p_refY) }, \
         { "dot2_p_refZ", NULL, MAVLINK_TYPE_FLOAT, 0, 40, offsetof(mavlink_unibo_references_t, dot2_p_refZ) }, \
         { "dot3_p_refX", NULL, MAVLINK_TYPE_FLOAT, 0, 44, offsetof(mavlink_unibo_references_t, dot3_p_refX) }, \
         { "dot3_p_refY", NULL, MAVLINK_TYPE_FLOAT, 0, 48, offsetof(mavlink_unibo_references_t, dot3_p_refY) }, \
         { "dot3_p_refZ", NULL, MAVLINK_TYPE_FLOAT, 0, 52, offsetof(mavlink_unibo_references_t, dot3_p_refZ) }, \
         { "dot4_p_refX", NULL, MAVLINK_TYPE_FLOAT, 0, 56, offsetof(mavlink_unibo_references_t, dot4_p_refX) }, \
         { "dot4_p_refY", NULL, MAVLINK_TYPE_FLOAT, 0, 60, offsetof(mavlink_unibo_references_t, dot4_p_refY) }, \
         { "dot4_p_refZ", NULL, MAVLINK_TYPE_FLOAT, 0, 64, offsetof(mavlink_unibo_references_t, dot4_p_refZ) }, \
         { "psi_ref", NULL, MAVLINK_TYPE_FLOAT, 0, 68, offsetof(mavlink_unibo_references_t, psi_ref) }, \
         { "dot_psi_ref", NULL, MAVLINK_TYPE_FLOAT, 0, 72, offsetof(mavlink_unibo_references_t, dot_psi_ref) }, \
         { "dot2_psi_ref", NULL, MAVLINK_TYPE_FLOAT, 0, 76, offsetof(mavlink_unibo_references_t, dot2_psi_ref) }, \
         { "Thrust", NULL, MAVLINK_TYPE_FLOAT, 0, 80, offsetof(mavlink_unibo_references_t, Thrust) }, \
         { "q0", NULL, MAVLINK_TYPE_FLOAT, 0, 84, offsetof(mavlink_unibo_references_t, q0) }, \
         { "q1", NULL, MAVLINK_TYPE_FLOAT, 0, 88, offsetof(mavlink_unibo_references_t, q1) }, \
         { "q2", NULL, MAVLINK_TYPE_FLOAT, 0, 92, offsetof(mavlink_unibo_references_t, q2) }, \
         { "q3", NULL, MAVLINK_TYPE_FLOAT, 0, 96, offsetof(mavlink_unibo_references_t, q3) }, \
         { "buttons", NULL, MAVLINK_TYPE_UINT32_T, 0, 100, offsetof(mavlink_unibo_references_t, buttons) }, \
         } \
}


/**
 * @brief Pack a unibo_references message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param p_refX 
 * @param p_refY 
 * @param p_refZ 
 * @param dot_p_refX 
 * @param dot_p_refY 
 * @param dot_p_refZ 
 * @param dot2_p_refX 
 * @param dot2_p_refY 
 * @param dot2_p_refZ 
 * @param dot3_p_refX 
 * @param dot3_p_refY 
 * @param dot3_p_refZ 
 * @param dot4_p_refX 
 * @param dot4_p_refY 
 * @param dot4_p_refZ 
 * @param psi_ref 
 * @param dot_psi_ref 
 * @param dot2_psi_ref 
 * @param Thrust 
 * @param q0 
 * @param q1 
 * @param q2 
 * @param q3 
 * @param buttons 
 * @param Tstamp 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_unibo_references_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       float p_refX, float p_refY, float p_refZ, float dot_p_refX, float dot_p_refY, float dot_p_refZ, float dot2_p_refX, float dot2_p_refY, float dot2_p_refZ, float dot3_p_refX, float dot3_p_refY, float dot3_p_refZ, float dot4_p_refX, float dot4_p_refY, float dot4_p_refZ, float psi_ref, float dot_psi_ref, float dot2_psi_ref, float Thrust, float q0, float q1, float q2, float q3, uint32_t buttons, uint64_t Tstamp)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_UNIBO_REFERENCES_LEN];
	_mav_put_uint64_t(buf, 0, Tstamp);
	_mav_put_float(buf, 8, p_refX);
	_mav_put_float(buf, 12, p_refY);
	_mav_put_float(buf, 16, p_refZ);
	_mav_put_float(buf, 20, dot_p_refX);
	_mav_put_float(buf, 24, dot_p_refY);
	_mav_put_float(buf, 28, dot_p_refZ);
	_mav_put_float(buf, 32, dot2_p_refX);
	_mav_put_float(buf, 36, dot2_p_refY);
	_mav_put_float(buf, 40, dot2_p_refZ);
	_mav_put_float(buf, 44, dot3_p_refX);
	_mav_put_float(buf, 48, dot3_p_refY);
	_mav_put_float(buf, 52, dot3_p_refZ);
	_mav_put_float(buf, 56, dot4_p_refX);
	_mav_put_float(buf, 60, dot4_p_refY);
	_mav_put_float(buf, 64, dot4_p_refZ);
	_mav_put_float(buf, 68, psi_ref);
	_mav_put_float(buf, 72, dot_psi_ref);
	_mav_put_float(buf, 76, dot2_psi_ref);
	_mav_put_float(buf, 80, Thrust);
	_mav_put_float(buf, 84, q0);
	_mav_put_float(buf, 88, q1);
	_mav_put_float(buf, 92, q2);
	_mav_put_float(buf, 96, q3);
	_mav_put_uint32_t(buf, 100, buttons);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_UNIBO_REFERENCES_LEN);
#else
	mavlink_unibo_references_t packet;
	packet.Tstamp = Tstamp;
	packet.p_refX = p_refX;
	packet.p_refY = p_refY;
	packet.p_refZ = p_refZ;
	packet.dot_p_refX = dot_p_refX;
	packet.dot_p_refY = dot_p_refY;
	packet.dot_p_refZ = dot_p_refZ;
	packet.dot2_p_refX = dot2_p_refX;
	packet.dot2_p_refY = dot2_p_refY;
	packet.dot2_p_refZ = dot2_p_refZ;
	packet.dot3_p_refX = dot3_p_refX;
	packet.dot3_p_refY = dot3_p_refY;
	packet.dot3_p_refZ = dot3_p_refZ;
	packet.dot4_p_refX = dot4_p_refX;
	packet.dot4_p_refY = dot4_p_refY;
	packet.dot4_p_refZ = dot4_p_refZ;
	packet.psi_ref = psi_ref;
	packet.dot_psi_ref = dot_psi_ref;
	packet.dot2_psi_ref = dot2_psi_ref;
	packet.Thrust = Thrust;
	packet.q0 = q0;
	packet.q1 = q1;
	packet.q2 = q2;
	packet.q3 = q3;
	packet.buttons = buttons;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_UNIBO_REFERENCES_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_UNIBO_REFERENCES;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_UNIBO_REFERENCES_LEN, MAVLINK_MSG_ID_UNIBO_REFERENCES_CRC);
#else
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_UNIBO_REFERENCES_LEN);
#endif
}

/**
 * @brief Pack a unibo_references message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param p_refX 
 * @param p_refY 
 * @param p_refZ 
 * @param dot_p_refX 
 * @param dot_p_refY 
 * @param dot_p_refZ 
 * @param dot2_p_refX 
 * @param dot2_p_refY 
 * @param dot2_p_refZ 
 * @param dot3_p_refX 
 * @param dot3_p_refY 
 * @param dot3_p_refZ 
 * @param dot4_p_refX 
 * @param dot4_p_refY 
 * @param dot4_p_refZ 
 * @param psi_ref 
 * @param dot_psi_ref 
 * @param dot2_psi_ref 
 * @param Thrust 
 * @param q0 
 * @param q1 
 * @param q2 
 * @param q3 
 * @param buttons 
 * @param Tstamp 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_unibo_references_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           float p_refX,float p_refY,float p_refZ,float dot_p_refX,float dot_p_refY,float dot_p_refZ,float dot2_p_refX,float dot2_p_refY,float dot2_p_refZ,float dot3_p_refX,float dot3_p_refY,float dot3_p_refZ,float dot4_p_refX,float dot4_p_refY,float dot4_p_refZ,float psi_ref,float dot_psi_ref,float dot2_psi_ref,float Thrust,float q0,float q1,float q2,float q3,uint32_t buttons,uint64_t Tstamp)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_UNIBO_REFERENCES_LEN];
	_mav_put_uint64_t(buf, 0, Tstamp);
	_mav_put_float(buf, 8, p_refX);
	_mav_put_float(buf, 12, p_refY);
	_mav_put_float(buf, 16, p_refZ);
	_mav_put_float(buf, 20, dot_p_refX);
	_mav_put_float(buf, 24, dot_p_refY);
	_mav_put_float(buf, 28, dot_p_refZ);
	_mav_put_float(buf, 32, dot2_p_refX);
	_mav_put_float(buf, 36, dot2_p_refY);
	_mav_put_float(buf, 40, dot2_p_refZ);
	_mav_put_float(buf, 44, dot3_p_refX);
	_mav_put_float(buf, 48, dot3_p_refY);
	_mav_put_float(buf, 52, dot3_p_refZ);
	_mav_put_float(buf, 56, dot4_p_refX);
	_mav_put_float(buf, 60, dot4_p_refY);
	_mav_put_float(buf, 64, dot4_p_refZ);
	_mav_put_float(buf, 68, psi_ref);
	_mav_put_float(buf, 72, dot_psi_ref);
	_mav_put_float(buf, 76, dot2_psi_ref);
	_mav_put_float(buf, 80, Thrust);
	_mav_put_float(buf, 84, q0);
	_mav_put_float(buf, 88, q1);
	_mav_put_float(buf, 92, q2);
	_mav_put_float(buf, 96, q3);
	_mav_put_uint32_t(buf, 100, buttons);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_UNIBO_REFERENCES_LEN);
#else
	mavlink_unibo_references_t packet;
	packet.Tstamp = Tstamp;
	packet.p_refX = p_refX;
	packet.p_refY = p_refY;
	packet.p_refZ = p_refZ;
	packet.dot_p_refX = dot_p_refX;
	packet.dot_p_refY = dot_p_refY;
	packet.dot_p_refZ = dot_p_refZ;
	packet.dot2_p_refX = dot2_p_refX;
	packet.dot2_p_refY = dot2_p_refY;
	packet.dot2_p_refZ = dot2_p_refZ;
	packet.dot3_p_refX = dot3_p_refX;
	packet.dot3_p_refY = dot3_p_refY;
	packet.dot3_p_refZ = dot3_p_refZ;
	packet.dot4_p_refX = dot4_p_refX;
	packet.dot4_p_refY = dot4_p_refY;
	packet.dot4_p_refZ = dot4_p_refZ;
	packet.psi_ref = psi_ref;
	packet.dot_psi_ref = dot_psi_ref;
	packet.dot2_psi_ref = dot2_psi_ref;
	packet.Thrust = Thrust;
	packet.q0 = q0;
	packet.q1 = q1;
	packet.q2 = q2;
	packet.q3 = q3;
	packet.buttons = buttons;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_UNIBO_REFERENCES_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_UNIBO_REFERENCES;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_UNIBO_REFERENCES_LEN, MAVLINK_MSG_ID_UNIBO_REFERENCES_CRC);
#else
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_UNIBO_REFERENCES_LEN);
#endif
}

/**
 * @brief Encode a unibo_references struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param unibo_references C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_unibo_references_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_unibo_references_t* unibo_references)
{
	return mavlink_msg_unibo_references_pack(system_id, component_id, msg, unibo_references->p_refX, unibo_references->p_refY, unibo_references->p_refZ, unibo_references->dot_p_refX, unibo_references->dot_p_refY, unibo_references->dot_p_refZ, unibo_references->dot2_p_refX, unibo_references->dot2_p_refY, unibo_references->dot2_p_refZ, unibo_references->dot3_p_refX, unibo_references->dot3_p_refY, unibo_references->dot3_p_refZ, unibo_references->dot4_p_refX, unibo_references->dot4_p_refY, unibo_references->dot4_p_refZ, unibo_references->psi_ref, unibo_references->dot_psi_ref, unibo_references->dot2_psi_ref, unibo_references->Thrust, unibo_references->q0, unibo_references->q1, unibo_references->q2, unibo_references->q3, unibo_references->buttons, unibo_references->Tstamp);
}

/**
 * @brief Encode a unibo_references struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param unibo_references C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_unibo_references_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_unibo_references_t* unibo_references)
{
	return mavlink_msg_unibo_references_pack_chan(system_id, component_id, chan, msg, unibo_references->p_refX, unibo_references->p_refY, unibo_references->p_refZ, unibo_references->dot_p_refX, unibo_references->dot_p_refY, unibo_references->dot_p_refZ, unibo_references->dot2_p_refX, unibo_references->dot2_p_refY, unibo_references->dot2_p_refZ, unibo_references->dot3_p_refX, unibo_references->dot3_p_refY, unibo_references->dot3_p_refZ, unibo_references->dot4_p_refX, unibo_references->dot4_p_refY, unibo_references->dot4_p_refZ, unibo_references->psi_ref, unibo_references->dot_psi_ref, unibo_references->dot2_psi_ref, unibo_references->Thrust, unibo_references->q0, unibo_references->q1, unibo_references->q2, unibo_references->q3, unibo_references->buttons, unibo_references->Tstamp);
}

/**
 * @brief Send a unibo_references message
 * @param chan MAVLink channel to send the message
 *
 * @param p_refX 
 * @param p_refY 
 * @param p_refZ 
 * @param dot_p_refX 
 * @param dot_p_refY 
 * @param dot_p_refZ 
 * @param dot2_p_refX 
 * @param dot2_p_refY 
 * @param dot2_p_refZ 
 * @param dot3_p_refX 
 * @param dot3_p_refY 
 * @param dot3_p_refZ 
 * @param dot4_p_refX 
 * @param dot4_p_refY 
 * @param dot4_p_refZ 
 * @param psi_ref 
 * @param dot_psi_ref 
 * @param dot2_psi_ref 
 * @param Thrust 
 * @param q0 
 * @param q1 
 * @param q2 
 * @param q3 
 * @param buttons 
 * @param Tstamp 
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_unibo_references_send(mavlink_channel_t chan, float p_refX, float p_refY, float p_refZ, float dot_p_refX, float dot_p_refY, float dot_p_refZ, float dot2_p_refX, float dot2_p_refY, float dot2_p_refZ, float dot3_p_refX, float dot3_p_refY, float dot3_p_refZ, float dot4_p_refX, float dot4_p_refY, float dot4_p_refZ, float psi_ref, float dot_psi_ref, float dot2_psi_ref, float Thrust, float q0, float q1, float q2, float q3, uint32_t buttons, uint64_t Tstamp)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_UNIBO_REFERENCES_LEN];
	_mav_put_uint64_t(buf, 0, Tstamp);
	_mav_put_float(buf, 8, p_refX);
	_mav_put_float(buf, 12, p_refY);
	_mav_put_float(buf, 16, p_refZ);
	_mav_put_float(buf, 20, dot_p_refX);
	_mav_put_float(buf, 24, dot_p_refY);
	_mav_put_float(buf, 28, dot_p_refZ);
	_mav_put_float(buf, 32, dot2_p_refX);
	_mav_put_float(buf, 36, dot2_p_refY);
	_mav_put_float(buf, 40, dot2_p_refZ);
	_mav_put_float(buf, 44, dot3_p_refX);
	_mav_put_float(buf, 48, dot3_p_refY);
	_mav_put_float(buf, 52, dot3_p_refZ);
	_mav_put_float(buf, 56, dot4_p_refX);
	_mav_put_float(buf, 60, dot4_p_refY);
	_mav_put_float(buf, 64, dot4_p_refZ);
	_mav_put_float(buf, 68, psi_ref);
	_mav_put_float(buf, 72, dot_psi_ref);
	_mav_put_float(buf, 76, dot2_psi_ref);
	_mav_put_float(buf, 80, Thrust);
	_mav_put_float(buf, 84, q0);
	_mav_put_float(buf, 88, q1);
	_mav_put_float(buf, 92, q2);
	_mav_put_float(buf, 96, q3);
	_mav_put_uint32_t(buf, 100, buttons);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_UNIBO_REFERENCES, buf, MAVLINK_MSG_ID_UNIBO_REFERENCES_LEN, MAVLINK_MSG_ID_UNIBO_REFERENCES_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_UNIBO_REFERENCES, buf, MAVLINK_MSG_ID_UNIBO_REFERENCES_LEN);
#endif
#else
	mavlink_unibo_references_t packet;
	packet.Tstamp = Tstamp;
	packet.p_refX = p_refX;
	packet.p_refY = p_refY;
	packet.p_refZ = p_refZ;
	packet.dot_p_refX = dot_p_refX;
	packet.dot_p_refY = dot_p_refY;
	packet.dot_p_refZ = dot_p_refZ;
	packet.dot2_p_refX = dot2_p_refX;
	packet.dot2_p_refY = dot2_p_refY;
	packet.dot2_p_refZ = dot2_p_refZ;
	packet.dot3_p_refX = dot3_p_refX;
	packet.dot3_p_refY = dot3_p_refY;
	packet.dot3_p_refZ = dot3_p_refZ;
	packet.dot4_p_refX = dot4_p_refX;
	packet.dot4_p_refY = dot4_p_refY;
	packet.dot4_p_refZ = dot4_p_refZ;
	packet.psi_ref = psi_ref;
	packet.dot_psi_ref = dot_psi_ref;
	packet.dot2_psi_ref = dot2_psi_ref;
	packet.Thrust = Thrust;
	packet.q0 = q0;
	packet.q1 = q1;
	packet.q2 = q2;
	packet.q3 = q3;
	packet.buttons = buttons;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_UNIBO_REFERENCES, (const char *)&packet, MAVLINK_MSG_ID_UNIBO_REFERENCES_LEN, MAVLINK_MSG_ID_UNIBO_REFERENCES_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_UNIBO_REFERENCES, (const char *)&packet, MAVLINK_MSG_ID_UNIBO_REFERENCES_LEN);
#endif
#endif
}

#if MAVLINK_MSG_ID_UNIBO_REFERENCES_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_unibo_references_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  float p_refX, float p_refY, float p_refZ, float dot_p_refX, float dot_p_refY, float dot_p_refZ, float dot2_p_refX, float dot2_p_refY, float dot2_p_refZ, float dot3_p_refX, float dot3_p_refY, float dot3_p_refZ, float dot4_p_refX, float dot4_p_refY, float dot4_p_refZ, float psi_ref, float dot_psi_ref, float dot2_psi_ref, float Thrust, float q0, float q1, float q2, float q3, uint32_t buttons, uint64_t Tstamp)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char *buf = (char *)msgbuf;
	_mav_put_uint64_t(buf, 0, Tstamp);
	_mav_put_float(buf, 8, p_refX);
	_mav_put_float(buf, 12, p_refY);
	_mav_put_float(buf, 16, p_refZ);
	_mav_put_float(buf, 20, dot_p_refX);
	_mav_put_float(buf, 24, dot_p_refY);
	_mav_put_float(buf, 28, dot_p_refZ);
	_mav_put_float(buf, 32, dot2_p_refX);
	_mav_put_float(buf, 36, dot2_p_refY);
	_mav_put_float(buf, 40, dot2_p_refZ);
	_mav_put_float(buf, 44, dot3_p_refX);
	_mav_put_float(buf, 48, dot3_p_refY);
	_mav_put_float(buf, 52, dot3_p_refZ);
	_mav_put_float(buf, 56, dot4_p_refX);
	_mav_put_float(buf, 60, dot4_p_refY);
	_mav_put_float(buf, 64, dot4_p_refZ);
	_mav_put_float(buf, 68, psi_ref);
	_mav_put_float(buf, 72, dot_psi_ref);
	_mav_put_float(buf, 76, dot2_psi_ref);
	_mav_put_float(buf, 80, Thrust);
	_mav_put_float(buf, 84, q0);
	_mav_put_float(buf, 88, q1);
	_mav_put_float(buf, 92, q2);
	_mav_put_float(buf, 96, q3);
	_mav_put_uint32_t(buf, 100, buttons);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_UNIBO_REFERENCES, buf, MAVLINK_MSG_ID_UNIBO_REFERENCES_LEN, MAVLINK_MSG_ID_UNIBO_REFERENCES_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_UNIBO_REFERENCES, buf, MAVLINK_MSG_ID_UNIBO_REFERENCES_LEN);
#endif
#else
	mavlink_unibo_references_t *packet = (mavlink_unibo_references_t *)msgbuf;
	packet->Tstamp = Tstamp;
	packet->p_refX = p_refX;
	packet->p_refY = p_refY;
	packet->p_refZ = p_refZ;
	packet->dot_p_refX = dot_p_refX;
	packet->dot_p_refY = dot_p_refY;
	packet->dot_p_refZ = dot_p_refZ;
	packet->dot2_p_refX = dot2_p_refX;
	packet->dot2_p_refY = dot2_p_refY;
	packet->dot2_p_refZ = dot2_p_refZ;
	packet->dot3_p_refX = dot3_p_refX;
	packet->dot3_p_refY = dot3_p_refY;
	packet->dot3_p_refZ = dot3_p_refZ;
	packet->dot4_p_refX = dot4_p_refX;
	packet->dot4_p_refY = dot4_p_refY;
	packet->dot4_p_refZ = dot4_p_refZ;
	packet->psi_ref = psi_ref;
	packet->dot_psi_ref = dot_psi_ref;
	packet->dot2_psi_ref = dot2_psi_ref;
	packet->Thrust = Thrust;
	packet->q0 = q0;
	packet->q1 = q1;
	packet->q2 = q2;
	packet->q3 = q3;
	packet->buttons = buttons;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_UNIBO_REFERENCES, (const char *)packet, MAVLINK_MSG_ID_UNIBO_REFERENCES_LEN, MAVLINK_MSG_ID_UNIBO_REFERENCES_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_UNIBO_REFERENCES, (const char *)packet, MAVLINK_MSG_ID_UNIBO_REFERENCES_LEN);
#endif
#endif
}
#endif

#endif

// MESSAGE UNIBO_REFERENCES UNPACKING


/**
 * @brief Get field p_refX from unibo_references message
 *
 * @return 
 */
static inline float mavlink_msg_unibo_references_get_p_refX(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Get field p_refY from unibo_references message
 *
 * @return 
 */
static inline float mavlink_msg_unibo_references_get_p_refY(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  12);
}

/**
 * @brief Get field p_refZ from unibo_references message
 *
 * @return 
 */
static inline float mavlink_msg_unibo_references_get_p_refZ(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  16);
}

/**
 * @brief Get field dot_p_refX from unibo_references message
 *
 * @return 
 */
static inline float mavlink_msg_unibo_references_get_dot_p_refX(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  20);
}

/**
 * @brief Get field dot_p_refY from unibo_references message
 *
 * @return 
 */
static inline float mavlink_msg_unibo_references_get_dot_p_refY(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  24);
}

/**
 * @brief Get field dot_p_refZ from unibo_references message
 *
 * @return 
 */
static inline float mavlink_msg_unibo_references_get_dot_p_refZ(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  28);
}

/**
 * @brief Get field dot2_p_refX from unibo_references message
 *
 * @return 
 */
static inline float mavlink_msg_unibo_references_get_dot2_p_refX(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  32);
}

/**
 * @brief Get field dot2_p_refY from unibo_references message
 *
 * @return 
 */
static inline float mavlink_msg_unibo_references_get_dot2_p_refY(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  36);
}

/**
 * @brief Get field dot2_p_refZ from unibo_references message
 *
 * @return 
 */
static inline float mavlink_msg_unibo_references_get_dot2_p_refZ(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  40);
}

/**
 * @brief Get field dot3_p_refX from unibo_references message
 *
 * @return 
 */
static inline float mavlink_msg_unibo_references_get_dot3_p_refX(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  44);
}

/**
 * @brief Get field dot3_p_refY from unibo_references message
 *
 * @return 
 */
static inline float mavlink_msg_unibo_references_get_dot3_p_refY(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  48);
}

/**
 * @brief Get field dot3_p_refZ from unibo_references message
 *
 * @return 
 */
static inline float mavlink_msg_unibo_references_get_dot3_p_refZ(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  52);
}

/**
 * @brief Get field dot4_p_refX from unibo_references message
 *
 * @return 
 */
static inline float mavlink_msg_unibo_references_get_dot4_p_refX(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  56);
}

/**
 * @brief Get field dot4_p_refY from unibo_references message
 *
 * @return 
 */
static inline float mavlink_msg_unibo_references_get_dot4_p_refY(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  60);
}

/**
 * @brief Get field dot4_p_refZ from unibo_references message
 *
 * @return 
 */
static inline float mavlink_msg_unibo_references_get_dot4_p_refZ(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  64);
}

/**
 * @brief Get field psi_ref from unibo_references message
 *
 * @return 
 */
static inline float mavlink_msg_unibo_references_get_psi_ref(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  68);
}

/**
 * @brief Get field dot_psi_ref from unibo_references message
 *
 * @return 
 */
static inline float mavlink_msg_unibo_references_get_dot_psi_ref(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  72);
}

/**
 * @brief Get field dot2_psi_ref from unibo_references message
 *
 * @return 
 */
static inline float mavlink_msg_unibo_references_get_dot2_psi_ref(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  76);
}

/**
 * @brief Get field Thrust from unibo_references message
 *
 * @return 
 */
static inline float mavlink_msg_unibo_references_get_Thrust(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  80);
}

/**
 * @brief Get field q0 from unibo_references message
 *
 * @return 
 */
static inline float mavlink_msg_unibo_references_get_q0(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  84);
}

/**
 * @brief Get field q1 from unibo_references message
 *
 * @return 
 */
static inline float mavlink_msg_unibo_references_get_q1(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  88);
}

/**
 * @brief Get field q2 from unibo_references message
 *
 * @return 
 */
static inline float mavlink_msg_unibo_references_get_q2(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  92);
}

/**
 * @brief Get field q3 from unibo_references message
 *
 * @return 
 */
static inline float mavlink_msg_unibo_references_get_q3(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  96);
}

/**
 * @brief Get field buttons from unibo_references message
 *
 * @return 
 */
static inline uint32_t mavlink_msg_unibo_references_get_buttons(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint32_t(msg,  100);
}

/**
 * @brief Get field Tstamp from unibo_references message
 *
 * @return 
 */
static inline uint64_t mavlink_msg_unibo_references_get_Tstamp(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint64_t(msg,  0);
}

/**
 * @brief Decode a unibo_references message into a struct
 *
 * @param msg The message to decode
 * @param unibo_references C-struct to decode the message contents into
 */
static inline void mavlink_msg_unibo_references_decode(const mavlink_message_t* msg, mavlink_unibo_references_t* unibo_references)
{
#if MAVLINK_NEED_BYTE_SWAP
	unibo_references->Tstamp = mavlink_msg_unibo_references_get_Tstamp(msg);
	unibo_references->p_refX = mavlink_msg_unibo_references_get_p_refX(msg);
	unibo_references->p_refY = mavlink_msg_unibo_references_get_p_refY(msg);
	unibo_references->p_refZ = mavlink_msg_unibo_references_get_p_refZ(msg);
	unibo_references->dot_p_refX = mavlink_msg_unibo_references_get_dot_p_refX(msg);
	unibo_references->dot_p_refY = mavlink_msg_unibo_references_get_dot_p_refY(msg);
	unibo_references->dot_p_refZ = mavlink_msg_unibo_references_get_dot_p_refZ(msg);
	unibo_references->dot2_p_refX = mavlink_msg_unibo_references_get_dot2_p_refX(msg);
	unibo_references->dot2_p_refY = mavlink_msg_unibo_references_get_dot2_p_refY(msg);
	unibo_references->dot2_p_refZ = mavlink_msg_unibo_references_get_dot2_p_refZ(msg);
	unibo_references->dot3_p_refX = mavlink_msg_unibo_references_get_dot3_p_refX(msg);
	unibo_references->dot3_p_refY = mavlink_msg_unibo_references_get_dot3_p_refY(msg);
	unibo_references->dot3_p_refZ = mavlink_msg_unibo_references_get_dot3_p_refZ(msg);
	unibo_references->dot4_p_refX = mavlink_msg_unibo_references_get_dot4_p_refX(msg);
	unibo_references->dot4_p_refY = mavlink_msg_unibo_references_get_dot4_p_refY(msg);
	unibo_references->dot4_p_refZ = mavlink_msg_unibo_references_get_dot4_p_refZ(msg);
	unibo_references->psi_ref = mavlink_msg_unibo_references_get_psi_ref(msg);
	unibo_references->dot_psi_ref = mavlink_msg_unibo_references_get_dot_psi_ref(msg);
	unibo_references->dot2_psi_ref = mavlink_msg_unibo_references_get_dot2_psi_ref(msg);
	unibo_references->Thrust = mavlink_msg_unibo_references_get_Thrust(msg);
	unibo_references->q0 = mavlink_msg_unibo_references_get_q0(msg);
	unibo_references->q1 = mavlink_msg_unibo_references_get_q1(msg);
	unibo_references->q2 = mavlink_msg_unibo_references_get_q2(msg);
	unibo_references->q3 = mavlink_msg_unibo_references_get_q3(msg);
	unibo_references->buttons = mavlink_msg_unibo_references_get_buttons(msg);
#else
	memcpy(unibo_references, _MAV_PAYLOAD(msg), MAVLINK_MSG_ID_UNIBO_REFERENCES_LEN);
#endif
}
