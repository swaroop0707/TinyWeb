/*
*Author:GeneralSandman
*Code:https://github.com/GeneralSandman/TinyWeb
*E-mail:generalsandman@163.com
*Web:www.generalsandman.cn
*/

/*---Basic of Http Protocol---
*This file definite the status,methods,errors of Http,
*http_test.cc can teach you how to use this header file.
****************************************
*
*/

#ifndef HTTP_H
#define HTTP_H

#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))
#define ELEM_AT(a, i, v) ((unsigned int)(i) < ARRAY_SIZE(a) ? (a)[(i)] : (v))

/* begin Http status */
#define HTTP_STATUS_MAP(XX)                                                   \
    XX(100, CONTINUE, Continue)                                               \
    XX(101, SWITCHING_PROTOCOLS, Switching Protocols)                         \
    XX(102, PROCESSING, Processing)                                           \
    XX(200, OK, OK)                                                           \
    XX(201, CREATED, Created)                                                 \
    XX(202, ACCEPTED, Accepted)                                               \
    XX(203, NON_AUTHORITATIVE_INFORMATION, Non - Authoritative Information)   \
    XX(204, NO_CONTENT, No Content)                                           \
    XX(205, RESET_CONTENT, Reset Content)                                     \
    XX(206, PARTIAL_CONTENT, Partial Content)                                 \
    XX(207, MULTI_STATUS, Multi - Status)                                     \
    XX(208, ALREADY_REPORTED, Already Reported)                               \
    XX(226, IM_USED, IM Used)                                                 \
    XX(300, MULTIPLE_CHOICES, Multiple Choices)                               \
    XX(301, MOVED_PERMANENTLY, Moved Permanently)                             \
    XX(302, FOUND, Found)                                                     \
    XX(303, SEE_OTHER, See Other)                                             \
    XX(304, NOT_MODIFIED, Not Modified)                                       \
    XX(305, USE_PROXY, Use Proxy)                                             \
    XX(307, TEMPORARY_REDIRECT, Temporary Redirect)                           \
    XX(308, PERMANENT_REDIRECT, Permanent Redirect)                           \
    XX(400, BAD_REQUEST, Bad Request)                                         \
    XX(401, UNAUTHORIZED, Unauthorized)                                       \
    XX(402, PAYMENT_REQUIRED, Payment Required)                               \
    XX(403, FORBIDDEN, Forbidden)                                             \
    XX(404, NOT_FOUND, Not Found)                                             \
    XX(405, METHOD_NOT_ALLOWED, Method Not Allowed)                           \
    XX(406, NOT_ACCEPTABLE, Not Acceptable)                                   \
    XX(407, PROXY_AUTHENTICATION_REQUIRED, Proxy Authentication Required)     \
    XX(408, REQUEST_TIMEOUT, Request Timeout)                                 \
    XX(409, CONFLICT, Conflict)                                               \
    XX(410, GONE, Gone)                                                       \
    XX(411, LENGTH_REQUIRED, Length Required)                                 \
    XX(412, PRECONDITION_FAILED, Precondition Failed)                         \
    XX(413, PAYLOAD_TOO_LARGE, Payload Too Large)                             \
    XX(414, URI_TOO_LONG, URI Too Long)                                       \
    XX(415, UNSUPPORTED_MEDIA_TYPE, Unsupported Media Type)                   \
    XX(416, RANGE_NOT_SATISFIABLE, Range Not Satisfiable)                     \
    XX(417, EXPECTATION_FAILED, Expectation Failed)                           \
    XX(421, MISDIRECTED_REQUEST, Misdirected Request)                         \
    XX(422, UNPROCESSABLE_ENTITY, Unprocessable Entity)                       \
    XX(423, LOCKED, Locked)                                                   \
    XX(424, FAILED_DEPENDENCY, Failed Dependency)                             \
    XX(426, UPGRADE_REQUIRED, Upgrade Required)                               \
    XX(428, PRECONDITION_REQUIRED, Precondition Required)                     \
    XX(429, TOO_MANY_REQUESTS, Too Many Requests)                             \
    XX(431, REQUEST_HEADER_FIELDS_TOO_LARGE, Request Header Fields Too Large) \
    XX(451, UNAVAILABLE_FOR_LEGAL_REASONS, Unavailable For Legal Reasons)     \
    XX(500, INTERNAL_SERVER_ERROR, Internal Server Error)                     \
    XX(501, NOT_IMPLEMENTED, Not Implemented)                                 \
    XX(502, BAD_GATEWAY, Bad Gateway)                                         \
    XX(503, SERVICE_UNAVAILABLE, Service Unavailable)                         \
    XX(504, GATEWAY_TIMEOUT, Gateway Timeout)                                 \
    XX(505, HTTP_VERSION_NOT_SUPPORTED, HTTP Version Not Supported)           \
    XX(506, VARIANT_ALSO_NEGOTIATES, Variant Also Negotiates)                 \
    XX(507, INSUFFICIENT_STORAGE, Insufficient Storage)                       \
    XX(508, LOOP_DETECTED, Loop Detected)                                     \
    XX(510, NOT_EXTENDED, Not Extended)                                       \
    XX(511, NETWORK_AUTHENTICATION_REQUIRED, Network Authentication Required)

enum http_status
{
#define XX(num, name, string) HTTP_STATUS_##name = num,
    HTTP_STATUS_MAP(XX)
#undef XX
};

/*Array statusStrings is used by httpStatueStr()*/
static const char *statusStrings[] =
    {
#define XX(num, name, string) #string,
        HTTP_STATUS_MAP(XX)
#undef XX
};

const char *httpStatusStr(enum http_status s)
{
    return ELEM_AT(statusStrings, s, "<invalid>");
}

    /* end Http status */

    /* begin Http Request Methods */

#define HTTP_METHOD_MAP(XX)          \
    XX(0, DELETE, DELETE)            \
    XX(1, GET, GET)                  \
    XX(2, HEAD, HEAD)                \
    XX(3, POST, POST)                \
    XX(4, PUT, PUT)                  \
    /* pathological */               \
    XX(5, CONNECT, CONNECT)          \
    XX(6, OPTIONS, OPTIONS)          \
    XX(7, TRACE, TRACE)              \
    /* WebDAV */                     \
    XX(8, COPY, COPY)                \
    XX(9, LOCK, LOCK)                \
    XX(10, MKCOL, MKCOL)             \
    XX(11, MOVE, MOVE)               \
    XX(12, PROPFIND, PROPFIND)       \
    XX(13, PROPPATCH, PROPPATCH)     \
    XX(14, SEARCH, SEARCH)           \
    XX(15, UNLOCK, UNLOCK)           \
    XX(16, BIND, BIND)               \
    XX(17, REBIND, REBIND)           \
    XX(18, UNBIND, UNBIND)           \
    XX(19, ACL, ACL)                 \
    /* subversion */                 \
    XX(20, REPORT, REPORT)           \
    XX(21, MKACTIVITY, MKACTIVITY)   \
    XX(22, CHECKOUT, CHECKOUT)       \
    XX(23, MERGE, MERGE)             \
    /* upnp */                       \
    XX(24, MSEARCH, M - SEARCH)      \
    XX(25, NOTIFY, NOTIFY)           \
    XX(26, SUBSCRIBE, SUBSCRIBE)     \
    XX(27, UNSUBSCRIBE, UNSUBSCRIBE) \
    /* RFC-5789 */                   \
    XX(28, PATCH, PATCH)             \
    XX(29, PURGE, PURGE)             \
    /* CalDAV */                     \
    XX(30, MKCALENDAR, MKCALENDAR)   \
    /* RFC-2068, section 19.6.1.2 */ \
    XX(31, LINK, LINK)               \
    XX(32, UNLINK, UNLINK)           \
    /* icecast */                    \
    XX(33, SOURCE, SOURCE)

enum http_method
{
#define XX(num, name, string) HTTP_##name = num,
    HTTP_METHOD_MAP(XX)
#undef XX
};

/*Array methodString is used by httpMethodStr()*/
static const char *methodStrings[] =
    {
#define XX(num, name, string) #string,
        HTTP_METHOD_MAP(XX)
#undef XX
};

const char *httpMethodStr(enum http_method m)
{
    return ELEM_AT(methodStrings, m, "<unknown>");
}

    /* end Http Request Methods */

    /* begin Http Errors */

#define HTTP_ERRNO_MAP(XX)                                              \
    /* No error */                                                      \
    XX(OK, "success")                                                   \
                                                                        \
    /* Callback-related errors */                                       \
    XX(CB_message_begin, "the on_message_begin callback failed")        \
    XX(CB_url, "the on_url callback failed")                            \
    XX(CB_header_field, "the on_header_field callback failed")          \
    XX(CB_header_value, "the on_header_value callback failed")          \
    XX(CB_headers_complete, "the on_headers_complete callback failed")  \
    XX(CB_body, "the on_body callback failed")                          \
    XX(CB_message_complete, "the on_message_complete callback failed")  \
    XX(CB_status, "the on_status callback failed")                      \
    XX(CB_chunk_header, "the on_chunk_header callback failed")          \
    XX(CB_chunk_complete, "the on_chunk_complete callback failed")      \
                                                                        \
    /* Parsing-related errors */                                        \
    XX(INVALID_EOF_STATE, "stream ended at an unexpected time")         \
    XX(HEADER_OVERFLOW,                                                 \
       "too many header bytes seen; overflow detected")                 \
    XX(CLOSED_CONNECTION,                                               \
       "data received after completed connection: close message")       \
    XX(INVALID_VERSION, "invalid HTTP version")                         \
    XX(INVALID_STATUS, "invalid HTTP status code")                      \
    XX(INVALID_METHOD, "invalid HTTP method")                           \
    XX(INVALID_URL, "invalid URL")                                      \
    XX(INVALID_HOST, "invalid host")                                    \
    XX(INVALID_PORT, "invalid port")                                    \
    XX(INVALID_PATH, "invalid path")                                    \
    XX(INVALID_QUERY_STRING, "invalid query string")                    \
    XX(INVALID_FRAGMENT, "invalid fragment")                            \
    XX(LF_EXPECTED, "LF character expected")                            \
    XX(INVALID_HEADER_TOKEN, "invalid character in header")             \
    XX(INVALID_CONTENT_LENGTH,                                          \
       "invalid character in content-length header")                    \
    XX(UNEXPECTED_CONTENT_LENGTH,                                       \
       "unexpected content-length header")                              \
    XX(INVALID_CHUNK_SIZE,                                              \
       "invalid character in chunk size header")                        \
    XX(INVALID_CONSTANT, "invalid constant string")                     \
    XX(INVALID_INTERNAL_STATE, "encountered unexpected internal state") \
    XX(STRICT, "strict mode assertion failed")                          \
    XX(PAUSED, "parser is paused")                                      \
    XX(UNKNOWN, "an unknown error occurred")

/* Define HPE_* values for each errno value above */
#define HTTP_ERRNO_GEN(n, s) HPE_##n,
enum http_errno
{
    HTTP_ERRNO_MAP(HTTP_ERRNO_GEN)
};
#undef HTTP_ERRNO_GEN

/*Array errnoStrings is used by httpErrnoStr()*/
static const char *errnoStrings[] =
    {
#define XX(name, string) #string,
        HTTP_ERRNO_MAP(XX)
#undef XX
};

const char *httpErrnoStr(enum http_errno e)
{
    return ELEM_AT(errnoStrings, e, "<invalid>");
}

    /* end Http Errors */

#endif