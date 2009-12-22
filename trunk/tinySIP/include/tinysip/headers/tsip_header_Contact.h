/*
* Copyright (C) 2009 Mamadou Diop.
*
* Contact: Mamadou Diop <diopmamadou@yahoo.fr>
*	
* This file is part of Open Source Doubango Framework.
*
* DOUBANGO is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*	
* DOUBANGO is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU Lesser General Public License for more details.
*	
* You should have received a copy of the GNU General Public License
* along with DOUBANGO.
*
*/

/**@file tsip_header_Contact.h
 * @brief SIP header 'Contact' as per RFC 3261 subclause 20.1.
 *
 * @author Mamadou Diop <diopmamadou(at)yahoo.fr>
 *
 * @date Created: Sat Nov 8 16:54:58 2009 mdiop
 */
#ifndef _TSIP_HEADER_CONTACT_H_
#define _TSIP_HEADER_CONTACT_H_
#include "tinysip_config.h"
#include "tinysip/tsip_uri.h"
#include "tinysip/headers/tsip_header.h"

/**@def TSIP_HEADER_CONTACT_CREATE
* Creates new sip 'Contact' header.  You must call @ref TSIP_HEADER_CONTACT_SAFE_FREE to free the header.
* @sa TSIP_HEADER_CONTACT_SAFE_FREE.
*/
/**@def TSIP_HEADER_CONTACT_SAFE_FREE
* Safely free a sip 'Contact' header previously created using TSIP_HEADER_CONTACT_CREATE.
* @sa TSIP_HEADER_CONTACT_CREATE.
*/
#define TSIP_HEADER_CONTACT_CREATE()		tsk_object_new(tsip_header_Contact_def_t)
#define TSIP_HEADER_CONTACT_SAFE_FREE(self)	tsk_object_unref(self), self = 0

#define TSIP_CONTACT_CREATE()		tsk_object_new(tsip_contact_def_t)
#define TSIP_CONTACT_SAFE_FREE(self)	tsk_object_unref(self), self = 0

typedef struct tsip_contact_s
{
	TSK_DECLARE_OBJECT;

	char *display_name;
	tsip_uri_t *uri;
	int32_t expires;
	tsk_params_L_t *params;
}
tsip_contact_t;
typedef tsk_list_t tsip_contacts_L_t;


////////////////////////////////////////////////////////////////////////////////////////////////////
/// @struct	
///
/// @brief	SIP header 'Contact'.
/// @author	Mamadou
/// @date	12/3/2009
///
/// @par ABNF: Contact	= 	( "Contact" / "m" ) HCOLON ( STAR / (contact-param *(COMMA contact-param)))
/// contact-param	= 	(name-addr / addr-spec) *( SEMI contact-params)
/// contact-params	= 	c-p-q / c-p-expires / feature-param / temp-gruu / pub-gruu / c-p-instance / contact-extension
/// c-p-q	= 	"q" EQUAL qvalue
/// c-p-expires	= 	"expires" EQUAL delta-seconds
/// feature-param	= 	enc-feature-tag [ EQUAL   LDQUOT   (tag-value-list   /   string-value)   RDQUOT ]
/// enc-feature-tag	= 	base-tags / other-tags
/// base-tags	= 	"audio" / "automata" / "class" / "duplex" / "data" / "control" / "mobility" / "description" / "events" / "priority" / "methods" / "schemes" / "application" / "video" / "language" / "type" / "isfocus" / "actor" / "text" / "extensions"
/// other-tags	= 	"+"   ftag-name
/// ftag-name	= 	ALPHA *( ALPHA / DIGIT / "!" / "'" / "." / "-" / "%" )
/// tag-value-list	= 	tag-value *("," tag-value)
/// tag-value	= 	["!"] (token-nobang / boolean / numeric)
/// token-nobang	= 	1*( alphanum / "-" / "." / "%" / "*" / "_" / "+" / "`" / "'" / "~" )
/// boolean	= 	"TRUE" / "FALSE"
/// numeric	= 	"#" numeric-relation number
/// numeric-relation	= 	">=" / "<=" / "=" / (number ":")
/// number	= 	[ "+" / "-" ] 1*DIGIT ["." 0*DIGIT]
/// string-value	= 	"<" *(qdtext-no-abkt / quoted-pair ) ">"
/// qdtext-no-abkt	= 	LWS / %x21 / %x23-3B / %x3D / %x3F-5B / %x5D-7E / UTF8-NONASCII
/// temp-gruu	= 	"temp-gruu" EQUAL LDQUOT *( qdtext / quoted-pair ) RDQUOT
/// pub-gruu	= 	"pub-gruu" EQUAL LDQUOT *( qdtext / quoted-pair ) RDQUOT
/// c-p-instance	= 	"+sip.instance" EQUAL LDQUOT "<" instance-val ">" RDQUOT
/// instance-val	= 	*uric
/// contact-extension	= 	generic-param
/// 	
////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct tsip_header_Contact_s
{	
	TSIP_DECLARE_HEADER;
	
	tsip_contacts_L_t *contacts;
}
tsip_header_Contact_t;

const tsip_contact_t *tsip_header_Contact_get_ContactAt(tsip_header_Contact_t *hdr_contact, size_t index);
#define tsip_header_Contact_get_Contact(hdr_contact) tsip_header_Contact_get_ContactAt(hdr_contact, 0)

tsip_header_Contact_t *tsip_header_Contact_parse(const char *data, size_t size);

TINYSIP_API const void *tsip_header_Contact_def_t;
TINYSIP_API const void *tsip_contact_def_t;

#endif /* _TSIP_HEADER_CONTACT_H_ */