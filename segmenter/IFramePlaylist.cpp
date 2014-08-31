/*
 * IFrameplaylist->cpp
 *
 *  Created on: Aug 6, 2014
 *      Author: satram
 */

#include "IFrameplaylist->h"
#include "IFrameIndex.h"
#include "Variantplaylist->h"

IFramePlaylist::IFramePlaylist() {
	playlist = new Playlist();

}

IFramePlaylist::~IFramePlaylist() {
	delete playlist;
}


void IFramePlaylist::add_header(ConfigParams & config)
{
}

void IFramePlaylist::update_node(IFrameIndex *index, VariantPlaylist *variant_playlist, bool addition)
{
	std::ostringstream oss;
	oss << "node-" << index->duration;
	if(addition)
	{
		Section node(oss.str());
		double duration = (double)index->duration / 1000.0;
		node.add_tag("INF", duration);
		oss.str("");
		oss << index->size << "@" << index->start_offset;
		node.add_tag("BYTERANGE", oss.str());
		node.set_path(variant_playlist->transcoded_output_url);
		node.set_locator(variant_playlist->transcoded_output_filename);
		playlist->add_section(node);
	}
	else
		playlist->delete_section(oss.str());
}



void IFramePlaylist::add_header(variant_stream_info &stream_info)
{
	Section header("header");
	header.add_tag("M3U");
	header.add_tag("VERSION", 4);
	header.add_tag("I-FRAMES-ONLY");
	playlist->add_section(header);
}

void IFramePlaylist::add_footer()
{
	Section footer ("footer");
	footer.add_tag("ENDLIST");
	playlist->add_section(footer);
}

void IFramePlaylist::finalize_playlist()
{
	add_footer();
}


