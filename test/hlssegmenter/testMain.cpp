/*
 * testMain.cpp
 *
 *  Created on: Aug 6, 2014
 *      Author: satram
 */

#include "segmenterCommon.h"

#define INP_BUF_SIZE (50 * TS_PKT_SIZE_BYTES)


int main(int argc, char *argv[])
{

	/*
	 * Set the input config parameters
	 */
	HlsConfigParams config;
#if 1
	config.playlist_type = EVENT;
#else
	config.playlist_type = LIVE;
	config.sliding_window_duration_ms = 9000;
#endif
	config.segment_duration_ms = 4000;
	config.web_server_url = "http://10.121.1.63:80/hlschunks/";
	config.output_folder = "/var/www/html/hlschunks/";

	variant_stream_info var1;
	var1.id = "quality1";
	var1.bandwidth = 1540000;
	var1.generate_iframe_url = true;
	var1.vid.codec = h264video;
	var1.vid.profile = "high";
	var1.vid.level = 3.1;
	var1.vid.resolution = "1280x720";
	var1.aud.codec = mpeg4audio_latm;
	var1.aud.subtype = "aac-lc";

	config.add_variant(var1);

	/*
	 * object for hls segmenter is created here
	 * this class can do segmentation based on config params
	 * and generate playlist as well
	 */
	Segmenter hls_segmenter(config);


    std::ifstream infile;
    infile.open(argv[1], std::ios::in | std::ios::binary);
    char *inp_buffer = new char[INP_BUF_SIZE];
    if(infile.is_open())
    {
        while(!infile.eof())
        {
        	infile.read(inp_buffer, INP_BUF_SIZE);
        	/*
        	 * send the input ts packets
        	 * both segmentation and playlist generation
        	 * happens inside this class
        	 */
        	//std::cout << ".";
        	hls_segmenter.parse_ts_packets(inp_buffer, infile.gcount());
        	std::this_thread::sleep_for(std::chrono::milliseconds(20));
        }
        infile.close();
        hls_segmenter.finalize_playlist();
    }
    delete inp_buffer;

	return 0;
}
