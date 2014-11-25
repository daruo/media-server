#ifndef _rtp_util_h_
#define _rtp_util_h_

// The Internet Protocol defines big-endian as the standard network byte order
#define nbo_r16 rtp_read_uint16
#define nbo_r32 rtp_read_uint32
#define nbo_w32 rtp_write_uint32

inline uint16_t rtp_read_uint16(const uint8_t* ptr)
{
	return (((uint16_t)ptr[0]) << 8) | ptr[1];
}

inline uint32_t rtp_read_uint32(const uint8_t* ptr)
{
	return (((uint32_t)ptr[0]) << 24) | (((uint32_t)ptr[1]) << 16) | (((uint32_t)ptr[2]) << 8) | ptr[3];
}

inline void rtp_write_uint32(uint8_t* ptr, uint32_t val)
{
	ptr[0] = (uint8_t)((val >> 24) & 0xFF);
	ptr[1] = (uint8_t)((val >> 16) & 0xFF);
	ptr[2] = (uint8_t)((val >> 8) & 0xFF);
	ptr[3] = (uint8_t)(val & 0xFF);
}

inline void nbo_write_rtp_header(uint8_t *ptr, const rtp_header_t *header)
{
	ptr[0] = (uint8_t)((header->v << 6) | (header->p << 5) | (header->x << 4) | header->cc);
	ptr[1] = (uint8_t)((header->m << 7) | header->pt);
	ptr[2] = (uint8_t)(header->seq >> 8);
	ptr[3] = (uint8_t)(header->seq & 0xFF);

	nbo_w32(ptr+4, header->timestamp);
	nbo_w32(ptr+8, header->ssrc);
}

inline void nbo_write_rtcp_header(uint8_t *ptr, const rtcp_header_t *header)
{
	ptr[0] = (uint8_t)((header->v << 6) | (header->p << 5) | header->rc);
	ptr[1] = (uint8_t)(header->pt);
	ptr[2] = (uint8_t)(header->length >> 8);
	ptr[3] = (uint8_t)(header->length & 0xFF);
}

#endif /* !_rtp_util_h_ */
