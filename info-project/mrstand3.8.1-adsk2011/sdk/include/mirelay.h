/******************************************************************************
 * Copyright 1986-2010 by mental images GmbH, Fasanenstr. 81, D-10623 Berlin,
 * Germany. All rights reserved.
 ******************************************************************************
 * Created:	29.10.2009
 * Purpose:	extended header file for mental ray applications
 *
 * Note: This file is generated automatically from the mental ray sources, do
 * not edit. Some definitions exist for internal reasons and are subject to
 * change between mental ray versions. See the mental ray user's manual for
 * a definitive description of the shader interface, and the Integrating mental
 * ray manual for a definitive description of the integration API.
 *****************************************************************************/

#ifndef MIRELAY_H
#define MIRELAY_H

#include <stdlib.h>	/* for size_t */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef RAY2
 #error you must include shader.h and geoshader.h
#endif


/*------------ mi_raylib.h ------------*/


/** define C linkage for function prototypes */
#ifndef miC_LINKAGE
#if defined(__cplusplus)
#define miC_LINKAGE extern "C"
#else
#define miC_LINKAGE
#endif
#endif


/*------------ mi_lib.h ------------*/

miBoolean	mi_raylib_init		(const miBoolean, const int,
					 const miBoolean);
void		mi_raylib_exit		(void);
const char	*mi_raylib_version	(void);
const char	*mi_raylib_date		(void);
const char	*mi_raylib_arch		(void);
miBoolean 	mi_raylib_attach_process(void);
miBoolean 	mi_raylib_detach_process(void);
#define miERR_FATAL	0x01		/* fatal errors */
#define miERR_ERROR	0x02		/* recoverable errors only */
#define miERR_WARNING	0x04		/* warnings */
#define miERR_INFO	0x08		/* informational messages */
#define miERR_PROGRESS	0x10		/* progress reports */
#define miERR_DEBUG	0x20		/* standard debugging messages */
#define miERR_VDEBUG	0x40		/* verbose debugging messages */

#define miERR_NONE	0		/* no messages */
#define miERR_ALL	(~0)		/* all messages */
#define miERR_DEFAULT	(miERR_FATAL | miERR_ERROR | miERR_WARNING)

#define miMSG_PHASE	0x0001		/* begin parse, tess, rendering... */
#define miMSG_PROGRESS	0x0002		/* percentages, #lines, #surfaces... */
#define miMSG_VPROGRESS	0x0004		/* verbose progress (per-task etc) */
#define miMSG_RUNTIME	0x0008		/* gettimeofday phase timing */
#define miMSG_SCENE	0x0010		/* stats: #tris, #boxes, #voxels... */
#define miMSG_MEMORY	0x0020		/* memory usage */
#define miMSG_RENDER	0x0040		/* RC stats: #rays, #samples, ... */
#define miMSG_VRENDER	0x0080		/* verbose RC: cache, calls, types...*/
#define miMSG_RESOURCES	0x0100		/* internal: task queues, memblks... */
#define miMSG_NETWORK	0x0200		/* startup/shutdown, nthreads, ncpus */
#define miMSG_FILES	0x0400		/* include/texture/output r/w, subst */
#define miMSG_DEBUG	0x0800		/* miscellaneous module debug msgs */
#define miMSG_MSGCODE	0x1000		/* errors/warnings print message code*/
#define miMSG_MSGTRANS	0x2000		/* errors/warnings print transaction */
#define miMSG_TESSELLATE 0x4000		/* info about number of triangles etc*/

#define miMSG_NONE	0x00000000	/* no messages */
#define miMSG_DEF	0x0000107f	/* default messages */
#define miMSG_USER	0xff000000	/* module-defined extras */
#define miMSG_ALL	0xffffffff	/* all messages */

void		mi_set_verbosity	(const int);	/* miERR_* bitmap */
int		mi_get_verbosity	(void);		/* miERR_* bitmap */
void		mi_set_subverbosity	(const miModule, const miUint);
miUint		mi_get_subverbosity	(const miModule);
miBoolean	mi_parse_subverbosity	(miUint *, const char *);

/* This function allows integrations to install a handler which is
   called instead of exit(), when a fatal condition occurs in ray.
   The previous handler is returned. Note that the handler may not
   return control to ray! */
typedef void (*miFatal_cb)(int);
miFatal_cb mi_fatal_handler(miFatal_cb fn);

void		mi_set_colormessage	(const char *argv);
void		mi_errorhandler		(void (* const)(const int,
					 const char * const,
					 const char * const, const int));
void		mi_fatal_error_freeze(void);
void		mi_version		(void);


/* registries pre-defined by the kernel */
#define miREG_RAY_VERSION  "{_MI_RAY_VERSION}"	/* mental ray version number */
#define miREG_RAY_MAJOR    "{_MI_RAY_MAJOR_VERSION}" /* ... major version */
#define miREG_RAY_MINOR    "{_MI_RAY_MINOR_VERSION}" /* ... minor version */
#define miREG_RAY_BRANCH   "{_MI_RAY_BRANCH}"	     /* ... branch version */
#define miREG_RAY_PLATFORM "{_MI_RAY_PLATFORM}" /* mental ray platform string */
#define miREG_RAY_SYSTEM   "{_MI_RAY_SYSTEM}"   /* mental ray system string */
#define miREG_RAY_DATE	   "{_MI_RAY_DATE}"     /* mental ray build date */
#define miREG_RAY_REVISION "{_MI_RAY_REVISION}"	/* mental ray repository revision */

void mi_lib_registry_print(
	void		*fp);		/* FILE to dump registry to, or 0 */

typedef enum miRl_mode {miRL_VALUE, miRL_VALUE_EXEC, miRL_LINK, miRL_CODE,
                        miRL_MI, miRL_SPDL, miRL_ECHO, miRL_SYSTEM } miRl_mode;

char *mi_lib_registry_lookup(
	const char	*name,		/* name of registry entry */
	miRl_mode	mode);		/* what to look up, exec side effects*/

/*------------ mi_trans.h ------------*/

miHostID mi_host_get(void);			/* getID */
miThreadID mi_thread_get(void);			/* getID */

/*------------ mi_ntlib.h ------------*/

void	mi_ntlib_init( void);
void	mi_ntlib_exit( void);

/*------------ mi_echo.h ------------*/

miBoolean mi_echo_scene(
	FILE		*fp,			/* file to print to */
	miTag		group_tag,		/* root group */
	miTag		camera_inst_tag,	/* camera instance tag */
	miTag		options_tag,		/* rendering options tag */
	miEchoOptions	*options);		/* echo options */

/*------------ mi_msg.h ------------*/

int mi_msg_no_of_cpus(void);                    /* physical number of local
                                                   cpus that can be called */
miBoolean mi_msg_is_slave(void);                /* tell, if I'm a slave */
void mi_msg_thread_stacksize(int size);
miThreadID mi_msg_register_thread(void);        /* register a foreign thread */
void mi_msg_unregister_thread(void);            /* unregister a thread       */
/* For WINDOWS platforms only: configure, if pipes are used for internal
   communication (miTRUE) or not. Set this to miTRUE before calling
   mi_raylib_init to force mental ray to not use sockets for internal
   communication to prevent firewalls from misrecognizing an Internet access.
   */
void mi_msg_pipe_mode_enabled(miBoolean enabled);
void mi_msg_add_hosts_from_list(char* const*list);

void mi_msg_add_host(const char* hostname, int socket_id);
void mi_msg_remove_host(const char* hostname);

void mi_msg_disable_rayhosts(void);

void mi_msg_add_rayhosts(void);
void mi_msg_add_rayhosts_nofile(void);

typedef void (*miHcbfunc)(int hid, miBoolean connect, int ncpus);
miHcbfunc mi_msg_register_hostcallback(miModule mod, miHcbfunc func);

const char* mi_msg_get_hostname(int host);

/*------------ mi_par.h ------------*/


/*
 * The flag parameter is a bitmap:
 *  1 = Bit 0	application abort (user pressed an abort button)
 *  2 = Bit 1	intra-raylib aborts that tells everybody that all tasks are
 *		finished and they can stop now. This is necessary because near
 *		the end threads will dequeue in-progress tasks, and as soon as
 *		the last in-progress task is finished the threads that are also
 *		working on the same task need to be killed _without_ doing an
 *		application abort, which may be pending and may not be reset.
 *  4 = Bit 2	threads are shutting down (mi_par_exit and mi_par_stop_threads
 *		called). The trans pointer is garbage in this case, and the
 *		mi_netthread_abort flag is set to tell the local net thread to
 *		exit (it can't look at transactions at this stage).
 *  8 = Bit 3	caught a fatal signal (from MSG sig_handler)
 * 16 = Bit 4	application wants an unconditional freezing of ray, which
 *		include stopping all threads. after this has been called, the
 *		process is no longer in a consistent state, and may not be
 *		re-called.
 */

#define miABORT_CLEAR        0
#define miABORT_APP          1
#define miABORT_RAY_DONE     2
#define miABORT_RAY_EXIT     4
#define miABORT_RAY_FATAL    8
#define miABORT_RAY_FREEZE  16

void mi_par_abort(int flag);	/* quit frame while it is running.   */
				/* 0=clear, m=set bit, ~m=clear bit. */
				/* use defines from above.           */

void mi_par_register_abortcallback(miBoolean (*callback)(void));

void mi_par_userthread(void (*mainfunc)(void* vpt), void* vptr);


/*------------ mi_mem.h ------------*/

/* host app memory management. all three parameters to mi_mem_set_allocator()
   must be given. by default, no flush callback is installed. the return
   values indicate whether the functions were successfully installed.
   mi_mem_set_allocator() must be called just before mi_mem_init(). the
   default allocators are automatically restored when MEM is shut down. */
typedef void *	(*miMem_alloc)		(size_t size);
typedef void *	(*miMem_realloc)	(void *mem, size_t size);
typedef void	(*miMem_free)		(void *mem);

miBoolean	mi_mem_set_allocator	(miMem_alloc    allocfn,
					 miMem_realloc  reallocfn,
					 miMem_free     freefn);

typedef size_t	(*miMem_flush_cb)	(size_t amount);

/* limit is the user limit set with -memory (in bytes) and allocated is the
   number of bytes currently allocated. we always have allocated > limit,
   which is the necessary condition for this callback to be called. */
typedef void	(*miMem_flush_failure_cb) (size_t limit, size_t allocated,
					   void *user_data);

miBoolean	mi_mem_set_flush_cb	(miMem_flush_cb flushcb);
miBoolean	mi_mem_set_flush_failure_cb (miMem_flush_failure_cb cb,
					     void *user_data);

size_t		mi_mem_flush		(size_t amount);
void		mi_mem_init		(void);

void		mi_mem_error_handler	(void (*)(void));
void		mi_mem_limit_handler	(miModule, miBoolean (*)(miUlong));
miUlong		mi_mem_memory_limit	(miUlong);

/*------------ mi_mi.h ------------*/

#define INCLUDE_PATH	\
	".;{_MI_REG_INCLUDE};/usr/local/mi/rayinc;/usr/include;/usr/include/mi"
typedef miBoolean (*miGetcCallBack)(FILE*);
typedef miBoolean (*miFrameCallBack)(miTag, miTag, miTag, miTag,miInh_func);

miBoolean mi_mi_parse(
	const char * 	mifilename,	/* file to parse, 0=stdin */
	miBoolean	resume,		/* resume parsing the current file */
	const char * 	incl_path,	/* include path (-I option) */
	const char * 	file_name,	/* overrides first output file type */
	const char * 	file_type,	/* overrides first output file name */
	miGetcCallBack	gcb,		/* getc-like function for scanner */
	miBoolean	verbose,	/* ignore verbose statement? */
	miFrameCallBack	fcb);		/* callback for every completed frame*/

miBoolean mi_mi_parse_rayrc(
	const char *	incl_path,	/* extra include path (-I option) */
	miBoolean	verbose);	/* ignore verbose statement? */

void mi_mi_translator(
	const char *	string,		/* translator command line */
	void		(*cb)(char *));	/* message callback or 0 */

miBoolean mi_mi_parse_assembly(	
	const char * 	mifilename);	/* file to parse */

/*------------ mi_img.h ------------*/

#if defined(_WIN32) && defined(_WINDOWS_)
/* do not force windows.h include in all IMG files */
typedef HANDLE miImg_file_handle;
#else
typedef int miImg_file_handle;
#endif

miBoolean mi_img_nread(
	miImg_file_handle	handle,
	void			*buf,
	int			count);
miBoolean mi_img_nwrite(
	miImg_file_handle	handle,
	void			*buf,
	int			count);
miBoolean mi_img_lseek(
	miImg_file_handle	handle,
	miUlong			offset);

miBoolean mi_img_custom_format(
	miImg_format	format,				/* format to install */
	miBoolean	(*test)	 (miImg_file * const, char * const),
	miBoolean	(*create)(miImg_file * const),
	miBoolean	(*open)	 (miImg_file * const, char * const),
	miBoolean	(*close) (miImg_file * const),
	miBoolean	(*read)	 (miImg_file * const, miImg_line * const),
	miBoolean	(*write) (miImg_file * const, miImg_line * const),
	miBoolean	tdown,
	const char	*name,
	miUint		tmap,
	int		btype,
	int		flags);

void mi_img_custom_format_error(
	miImg_file 		*ifp,			/* file struct */
	miImg_error		error,			/* error miIMG_ERR_* */
	int			os_error);		/* Unix/NT errno */
#define miIMG_CALLBACK_FATAL 1
#define miIMG_CALLBACK_CONTINUE 2

void		mi_img_err_handler(
				void (*cb)(miImg_file *));
void		mi_img_err_msg(
				miImg_file *);		/* file descriptor */
void		mi_img_debug(
				int);			/* debug level 0..3 */

void		mi_img_mode(
				miTag);			/* options tag */

/*------------ mi_scene.h ------------*/

typedef miBoolean (*miTraversal_func)(
	void		  *data,	/* opaque this pointer */
	struct miInstance *parent,	/* previously inherited instance */
	struct miInstance *inst,	/* new instance to be inherited */
	miTag		  *path,	/* path, begins with root group */
					/* and ends with curr DAG instance */
	int		  pathlen);	/* number of tags in path[] */

typedef struct miScene_preprocess {
	miTag		root_group;	/* root group of scene DAG */
	miTag		camera_inst;	/* which camera to use */
	miTag		options;	/* RC options for rendering */
	char		render_space;	/* renderer expects object stored in */
					/* 'c'amera or 'o'bject space */
	miUint1		fb_virtual;	/* using in memory/memmaped/cached fbs*/
	miCBoolean	spare;		/* not used */
	miBoolean	cache_boxes;	/* keep untransformed boxes (turntbl)*/
	miBoolean	delete_objects;	/* delete objects after tesselation */
	miBoolean	delete_accel;	/* delete RC acceleration structures */
	miBoolean	tessellate;	/* tessellate */
	miBoolean	assembly_prep;	/* asm preprocessing */
	double		time;		/* current time */
	miPointer	inheritance_func;
	miTraversal_func traversal_func;/* per-instance imatter callback */
	void		*traversal_data;/* opaque data for traversal_func */

	int		no_lights;	/* number of lights found */
	int		no_leaf_insts;	/* number of leaf instances found */
	int		no_boxes;	/* number of (shared) boxes found */
	miTag		lights;		/* first light leaf instance */
	miTag		leaf_insts;	/* first box leaf instance */
	miTag		cameras;	/* first camera leaf instance */
	miUint		max_texspace;	/* max number of texture spaces/obj */
	miInstance *	inh_instance;
} miScene_preprocess;

#define miSCENE_PREPROCESS_CONTROL_INIT(C) \
	(void)memset(&(C), 0, sizeof(C)); \
	(C).tessellate = miTRUE; \
	(C).assembly_prep = miFALSE; \
	(C).inh_instance = 0;
void *mi_scene_create	(miTag * const	tag,
			 const miScene_types	type, ...);
void *mi_scene_recreate	(miTag	tag,
			 const miScene_types	type, ...);
void mi_scene_incremental(void);
void mi_scene_incremental_end(void);
void mi_scene_checkpoint(void);
void mi_scene_checkpoint_end(void);
miBoolean mi_scene_check(const miTag	tag);
								/* group 2 */
void mi_scene_delete	(miTag	tag);
void mi_scene_delete_one(miTag	tag);
void mi_scene_link	(const miTag	ptag,
			 const miTag	ctag,
			 const int	which);
void mi_scene_unlink	(const miTag	gtag,
			 const miTag	otag,
			 const int	which);
miBoolean mi_scene_tesselate
			(miScene_preprocess * const control,
			 miBoolean		lineboxes);
const char *mi_scene_type_name(const miScene_types type);

void mi_scene_dump	(const miTag, const int);

void mi_scene_checkall	(const miTag);

void mi_scene_set_masterhost(miUint host);

/*------------ mi_job.h ------------*/

typedef enum {				/* type of progress, for callback */
	miJOBP_FINALGATHER,		/* finalgather preproc  */
	miJOBP_FASTLOOKUP,		/* fg fastlookup preproc */
	miJOBP_PHOTONEMISSION,		/* photon emission */
	miJOBP_RENDER,			/* standard rendering  */
	miJOBP_PHOTONREEMISSION,	/* photon re-emission */
	miJOBP_IMPORTONEMISSION,	/* importon emission */
	miJOBP_IMPORTONREEMISSION,	/* importon re-emission */
	miJOBP_AOPOINTEMISSION,		/* amb occl points emission */
	miJOBP_AOPOINTREEMISSION,	/* amb occl points re-emission */
	miJOBP_IPADAPTPROCESS,		/* irr particles geom variab comp */
	miJOBP_IPADAPTREPROCESS,	/* irr particles geom variab re-comp */
	miJOBP_IPINDPROCESS,		/* irr particles ind pass comp */
	miJOBP_IPINDREPROCESS,		/* irr particles ind pass re-comp */
	miJOBP_IPFINALPROCESS,		/* irr particles final irr pass comp */
	miJOBP_IPFINALREPROCESS,	/* irr particles final irr pass re-comp */
	miJOBP_IPTRACE,			/* irr particles tracing */
	miJOBP_IPRETRACE,		/* irr particles re-tracing */
	miJOBP_IPOPTIMIZE,		/* irr particles optimization */
	miJOBP_IPINTERPPOINTSEMIT,	/* irr particles interp points emission */
	miJOBP_IMPORTONOPTIMIZE,	/* importon optimization */
	miJOBP_N			/* number of legal values */
} miJob_progress;


typedef void (*miJob_progresscb)(
	miScalar	percent,	/* percent of task completed */
	miJob_progress 	current_task);	/* type of current task */

void mi_job_percent_register_cb(
	miJob_progresscb	callback);
miBoolean mi_job_set_nthreads(
	int		n);		/* run at this many threads */
miBoolean mi_job_set_slaves_only(
	miBoolean	setting);	/* if true, only slaves execute jobs */

miBoolean mi_job_set_slaves_active(
	miBoolean	setting);	/* if false, slaves are disabled */

miBoolean mi_job_set_disk_swapping(void); /* enable disk swapping */

/*------------ mi_api.h ------------*/

enum mi_symtab { S_GLOBAL=0, S_FUNCDECL, S_OPTIONS, S_CAMERA, S_LIGHT,
		 S_OBJECT, S_INSTANCE, S_INSTGROUP, S_MATERIAL,
		 S_CTEXTURE, S_STEXTURE, S_VTEXTURE, S_VARIABLE,
		 S_ASSEMBLY, S_MAPDECL,
		 S_MAP, S_METASL, S_NTYPES };

/*
 * optional features that must be enabled to work (mi_api_setfeature())
 */

typedef enum miApi_feature {
	miAPI_F_SPACECURVE = 0,
	miAPI_F_SUBDIVSURF = 1,
	miAPI_NFEATURES
} miApi_feature;

/*
 * texture search paths. Passed to mi_api_texpath_config by ray/ray_option.cpp
 */

#define miAPI_TEXPATH_ENV	"MI_TEXTURE_PATH"
#define miAPI_DEFAULT_TEXPATH	"{_MI_REG_TEXTURE};/usr/local/mi/texture;."

/*
 * light profile search paths. Passed to mi_api_lppath_config
 * by ray/ray_option.cpp
 */
#define miAPI_LPPATH_ENV	"MI_LIGHTPROFILE_PATH"
#define miAPI_DEFAULT_LPPATH	\
                "{_MI_REG_LIGHTPROFILE};/usr/local/mi/lightprofile;."

#define miAPI_ASMPATH_ENV	"MI_ASSEMBLY_PATH"
#define miAPI_DEFAULT_ASMPATH	"{_MI_REG_ASSEMBLY};."

/*
 * map search paths. Passed to mi_api_mappath_config by ray/ray_option.cpp
 */

#define miAPI_MAP_PATH_ENV	"MI_MAP_PATH"
#define miAPI_DEFAULT_MAP_PATH	"{_MI_REG_MAP};."

void	     mi_api_set_reload_limit	(miUint);
miUint	     mi_api_get_reload_limit	(void);

miBoolean mi_api_error_callback		(void (*)(const char *, int),
					 void (*)(const char *, int));
miBoolean mi_api_notify_callback	(void (*)(const char *, miTag, miTag, char));
int	     mi_api_setfeature		(miApi_feature, int);
void	     mi_api_error		(const char *, ...);
void	     mi_api_warning		(const char *, ...);
void	     mi_api_nerror		(int, const char *, ...);
void	     mi_api_nwarning		(int, const char *, ...);
/* only for ray 1.x compatibility. */
miBoolean mi_api_frame_begin		(struct miCamera **, struct miRc_options **);
miBoolean mi_api_view_transform		(miMatrix);
miBoolean mi_api_frame_end		(void);
miBoolean mi_api_code_verbatim_begin	(void);
miBoolean mi_api_code_verbatim_end	(void);
miBoolean mi_api_code_byte_copy		(int, miUchar *);
typedef struct miApi_typeinfo {		/* info about each parameter type: */
	enum miParam_type type;		/* expected value type */
	int		size;		/* size in bytes of one value */
	int		nval;		/* max # of values expected */
	char		code;		/* code char for string: s=scalar... */
	const char     *name;		/* type name string, for printing */
} miApi_typeinfo;

miApi_typeinfo *mi_api_get_typeinfo	(enum miParam_type);
miBoolean mi_api_gui_begin		(char *);
miBoolean mi_api_gui_end		(void);
miBoolean mi_api_gui_attr		(char *, enum miParam_type, int, ...);
miBoolean mi_api_gui_control_begin	(char *, char *);
miBoolean mi_api_gui_control_end	(void);
miBoolean mi_api_gui_push		(void);
miBoolean mi_api_gui_pop		(void);
miBoolean mi_api_gui_default		(miTag, char *, miBoolean);

/*------------ mi_shader.h ------------*/

typedef struct miRc_select {
		struct miRc_select *next;
		miRay_type	type;		/* type of the ray */
		miUint		label;		/* label of hit object */
		double		dist;		/* length of the ray */
		miVector	org;		/* ray origin */
		miVector	dir;		/* ray direction */
		miVector	point;		/* point of intersection */
		miVector	normal; 	/* interpolated normal */
		miVector	normal_geom;	/* geometric normal */
		miCBoolean	inv_normal;	/* normals are inverted */
		miTag		instance;	/* hit object instance */
		miTag		material;	/* material shader */
		miTag		volume; 	/* volume shader */
		float		bary[4];	/* barycentric coordinates */
		int		spare;		/* not used */
} miRc_select;

miRc_select *mi_rc_trace_select(
		int		x,		/* raster X coord to sample */
		int		y);		/* raster Y coord to sample */

/*------------ mi_rc.h ------------*/

/*
 * the main entry point. This is basically a front-end for rendering but
 * also does scene preprocessing and postprocessing, display connections,
 * frame buffer save/restore etc, based on the miRENDER mode flags.
 */

#define miRENDER_PREPROC	     0x000001	/* scene preprocessing */
#define miRENDER_OBJ_DELETE	     0x000002	/* delete source geometry */
#define miRENDER_SHADOWMAP	     0x000004	/* render shadow maps */
#define miRENDER_DISPLAY	     0x000008	/* connect imf_disp/imgpipe */
#define miRENDER_RENDER		     0x000010	/* render */
#define miRENDER_FB_SAVE	     0x000020	/* make copy of frame bufs */
#define miRENDER_FB_RESTORE	     0x000040	/* restore frame buf copy */
#define miRENDER_FB_DELETE	     0x000080	/* delete frame buf copy */
#define miRENDER_OUTPUTSH	     0x000100	/* call output shaders */
#define miRENDER_POSTPROC	     0x000200	/* scene postprocessing */
#define miRENDER_IMAGE_DELETE	     0x000400	/* delete frame buffers */
#define miRENDER_CHECK		     0x000800	/* debugging: check scene */
#define miRENDER_DUMP		     0x001000	/* debugging: dump to stdout */
#define miRENDER_ACCEL_DELETE	     0x002000	/* postproc: rm bsp tree etc */
#define miRENDER_LIGHTMAP	     0x004000	/* Process lightmaps */
#define miRENDER_REINHERIT	     0x008000	/* preprocess inheritance */
#define miRENDER_POSTPROC_FBC        0x010000	/* flush box cache        */
#define miRENDER_DISPLAY_FG	     0x020000	/* display FG precomputing */
#define miRENDER_RENDER_FG	     0x040000	/* render FG (not images) */
#define miRENDER_RENDER_PM	     0x080000	/* render photonmaps */
#define miRENDER_LIGHT_ACCEL_DELETE  0x100000	/* delete light acc. data */
#define miRENDER_REINHERIT_LIGHTS    0x200000	/* prepr. lights inheritance */
#define miRENDER_ASSEMBLY	     0x400000   /* prepr. assembly */

#define miRENDER_DEFAULT	     0x00471f	/* standard render+outputshd */
#define miRENDER_SHADOWMAP_ONLY      0x000207	/* render shadowmaps only */
#define miRENDER_FG_ONLY	     0x044607	/* render finalgather map only */
#define miRENDER_PM_ONLY	     0x084603	/* render photonmaps only */
#define miRENDER_LIGHTMAP_ONLY	     0x004607	/* render lightmaps only */

miC_LINKAGE miBoolean mi_rc_run(
	miUint			mode,		/* what to do... */
	int			imgpipe,	/* pipe to image fd if nz */
	unsigned int		prevmask,	/* pixel preview shader mask*/
	miTag			root_group,	/* root of scene to render */
	miTag			c_inst_tag,	/* camera instance */
	miTag			camera_tag,	/* camera (== inst->item) */
	miTag			option_tag,	/* RC options */
	miInh_func		inh_func);	/* inheritance function */

enum miRc_query {				/* for mi_rc_run_query */
						/* after preprocessing: */
	miRCQ_NO_LIGHTS,			/* # of light leaf insts */
	miRCQ_NO_LEAF_INSTS,			/* # of object leaf insts */
	miRCQ_LIGHTS,				/* list of light leaf insts */
	miRCQ_LEAF_INSTS,			/* list of object leaf insts */
	miRCQ_CAMERAS,				/* list of camera leaf insts */
						/* after render w/o IMG_DEL: */
	miRCQ_FB,				/* get frame buffer base */
	miRCQ_OPTIONS,				/* render options tag */
	miRCQ_NEEDS_PREPROC,			/* needs scene preprocessing?*/
	miRCQ_DISP_NET_PORT,			/* port used by imf_disp */
	miRCQ_DISP_TALK_PORT			/* port used by disp talk protocol */
};

miC_LINKAGE miBoolean mi_rc_run_query(
	enum miRc_query		mode,		/* what to query? */
	int			arg,		/* extra argument */
	void			*result);	/* returned value */

miC_LINKAGE void mi_rc_run_traversal_cb(
	miTraversal_func	cb,		/* traversal callback */
	void			*data);		/* opaque data for trav cb */
enum miRc_taskorder {
	miRC_TO_HILBERT = 0,
	miRC_TO_SPIRAL,
	miRC_TO_LEFT_RIGHT,
	miRC_TO_RIGHT_LEFT,
	miRC_TO_TOP_DOWN,
	miRC_TO_BOTTOM_UP
};

miC_LINKAGE void mi_rc_set_taskorder(	/* call before mi_rc_run. Valid only */
	enum miRc_taskorder o);		/* in the current transaction. */

/*------------ mi_disp.h ------------*/

typedef void	*miStream;
struct miRc_mapfb;

typedef void    (*miDisp_cb)(void *, struct miRc_mapfb *, int, int, int, int);
typedef void    (*miDisp_jpeg_cb)(void *, void *, int);

miStream  mi_disp_stream_pipe_begin	(int);
miStream  mi_disp_stream_socket_begin	(int);
miStream  mi_disp_stream_talk_begin	(int);
miStream  mi_disp_stream_cb_begin	(void *, miDisp_cb);
miStream  mi_disp_stream_jpeg_cb_begin	(void *, miDisp_jpeg_cb, int);
void	  mi_disp_stream_end		(miStream);
miImg_image * mi_disp_fbmap		(struct miRc_mapfb *, miUint buffer_index);
void          mi_disp_fbunmap		(struct miRc_mapfb *, miUint buffer_index);
miImg_image * mi_disp_fbmap_name	(struct miRc_mapfb *, const char *buffer_name);
void          mi_disp_fbunmap_name	(struct miRc_mapfb *, const char *buffer_name);

/* for backwards compatibility with mental ray 3.0 (without JPEG support): */
#define mi_disp_stream_start(R,J,A,Q) mi_disp_stream_cb_begin(A,R)

/*------------ mi_link.h ------------*/

#define miLINK_PATH_ENV "MI_LIBRARY_PATH"
#define miLINK_DEFAULT_PATH "{_MI_REG_LIBRARY};/usr/local/mi/lib;."
#define miLINK_REG_CPP_COMPILER       "{_MI_REG_CPP_COMPILER}"
#define miLINK_REG_CPP_COMPILER_FLAGS "{_MI_REG_CPP_COMPILER_FLAGS}"
#define miLINK_REG_LINKER	      "{_MI_REG_LINKER}"
#define miLINK_REG_LINKER_FLAGS	      "{_MI_REG_LINKER_FLAGS}"
#define miLINK_REG_MANIFEST_TOOL      "{_MI_REG_MANIFEST_TOOL}"

void mi_link_config(	/* initialize: */
    const char* l_cmd,		/* ld command (or 0) */
    const char* l_options,		/* ld options (or 0) */
    const char* c_cmd,		/* cc command (or 0) */
    const char* c_options,		/* cc options (or 0) */
    const char* l_path1,		/* user-defined path list (or 0) */
    const char* l_path2,		/* paths from environment variable (or 0) */
    const char* l_path3);		/* mental ray default path list */

void mi_link_set_module_handle(
    void	*mod);		/* handle for shader.lib (really HMODULE) */

void mi_link_register_builtin(
    const char* fname,		/* name of builtin function to be registered */
    const miFunction_ptr func); /* pointer to builtin function */


/* return maximal module id used */
int mi_link_module_max_id(void);

/* return the .so/.dll file name linked for the given id, or 0 if none */
const char *mi_link_module_name(
    int	module_id);		/* module id */


struct miLinkModule;
struct miLinkModule *mi_link_file_add(
    const char*   file,          /* name of a .c, .o or .so/.dll file */
    miBoolean     source,        /* .c instead of .o/.so? */
    miBoolean     verbatim,      /* came from $code .. $end code */
    miBoolean	  delaylink);    /* delay linking until mi_link_delayed() */

void mi_link_file_remove(
    const char*   file);         /* name of a .c, .o or .so/.dll file */


/*------------ rayso.h ------------*/

DLLIMPORT int mi_raylib_license_get(int licwanted);
DLLIMPORT void mi_raylib_license_release(void);
DLLIMPORT int mi_raylib_license_status(void);
DLLIMPORT void mi_raylib_license_mode(int);

/*------------ rcprogressive.h ------------*/


/******************************************************************************
 * PROGRESSIVE API
 *****************************************************************************/

/* buffer types supported for application display buffer */
typedef enum
{
  PROG_BUFFER_RGBA_8	= 0,	/* RGBA, 8bit */
  PROG_BUFFER_RGBA_32	= 1,	/* RGBA, 32bit fp */
} miRc_prog_buffer_type;

/* 
 * Set application display buffer.
 *
 * The call blocks until the progressive rendering core is
 * properly set up, then it triggers rendering and returns.
 * During a running rendering, a call is ignored.
 * \param display_buffer	display buffer on application side
 * \param stride		buffer stride
 * \param type  		buffer type
 * \param flip			flip image upside down
 * \param using_incremental	true if incremental changes are used
 * \return 	true on success, false if the progressive core is
 *		not running in interactive mode
 */
miBoolean mi_rc_progressive_set_buffer(
    void 			*display_buffer,
    size_t			stride,
    miRc_prog_buffer_type	type,
    miBoolean			flip,
    miBoolean			using_incremental 
#if defined(__cplusplus)
    = false
#endif
);


/* 
 * Set a global tonemapper.
 *
 * The tonemapping function will be called on the result that
 * is transferred to the display buffer. The result of this function
 * has to be in the interval [0,1], i.e. clamping has to be peformed
 * in the tonemapping function.
 * The tonemapping function can be changed at any point during
 * rendering (e.g. to adjust brightness of the displayed result),
 * with the following restriction:
 * The old tonemapping function still has to be callable until the
 * current frame is finished.
 * \param tonemapper	tonemappeing function to use on RGB
 * \param data		userdata pointer, that will be provided when the 
 *			tonemapping function is called
 */
void mi_rc_progressive_set_tonemapper_function(
    void	(*tonemapper)(float out[3], const float in[3], void* data), 
    void	*userdata 
#if defined(__cplusplus)
    = 0
#endif
);


/* The following two constants are special return values for
 * mi_rc_progressive_get_update_count(),
 * mi_rc_progressive_update_buffer(), and
 * mi_rc_progressive_update_buffer_first_subframe()
 */
enum {
    /* The core is not running (it might not have been started 
     * yet or already been shut down)
     */
    MI_RC_PROGRESSIVE_NOT_RUNNING = 0xfffffff,
    /* The core has finished rendering and is on hold until the
     * application calls mi_rc_progressive_shutdown()
     */
    MI_RC_PROGRESSIVE_FINISHED = 0xfffffff - 1
};

/*
 * Ask for the number of (sub)frames rendered by the core so far,
 * i.e. the number of updates for the result buffer
 * \return	current core (sub)frame count
 *		(also see special return values above)
 */
miUint mi_rc_progressive_get_update_count();

/*
 * Ask for application display buffer update and get current
 *
 * update counter.
 * The core locks the buffer and copies it's contents to the
 * application's buffer
 * \return 	(sub)frame count belonging to copied buffer
 *		(also see special return values above)
 */
miUint mi_rc_progressive_update_buffer();

/* 
 * Ask for cached first subframe update.
 *
 * The downsampled first subframe is scaled to full resolution
 * and then copied to the display buffer analogously to
 *  mi_rc_progressive_update_buffer()
 *  \return 	current (sub)frame count
 *		(also see special return values above)
 */
miUint mi_rc_progressive_update_buffer_first_subframe();

/*
 * Update current camera, restart rendering.
 * 
 * This methods triggers a rendering restart and starts to
 * render from the given camera position.
 * Currently, only aspect ratio, aperture, and focal length are
 * taken into account.
 * \param camera_instance	object to world camera transform
 * \param camera		camera
 */
void mi_rc_progressive_set_camera(
    const miMatrix	camera_instance,
    const miCamera	*camera);

/*
 * Stop a running rendering gracefully.
 *
 * The core will finish the current frame and then stay on hold as
 * if finished the rendering waiting for mi_rc_progressive_shutdown()
 */
void mi_rc_progressive_stop_rendering();

/* 
 * Cancel a running rendering.
 *
 * The core will stop computing pixels immediately and then
 * stay on hold as if finished the rendering waiting
 * for mi_rc_progressive_shutdown()
 */
void mi_rc_progressive_cancel_rendering();

/* 
 * Finalize rendering.
 *
 * This method has to be called after a rendering is finished (or has
 * been canceled or stopped). It blocks until the progressive rendering
 * core has been completely shut down.
 */
void mi_rc_progressive_shutdown();

void mi_rc_progressive_refine(
    size_t xl,
    size_t yl,
    size_t xh,
    size_t yh);


#ifdef __cplusplus
}
#endif

#endif
