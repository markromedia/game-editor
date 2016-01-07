#ifndef __JAVASCRIPT_DELEGATE_hpp
#define __JAVASCRIPT_DELEGATE_hpp

#include <Awesomium/JSObject.h>
#include <Awesomium/WebCore.h>

class AwesomiumHandler;


class JavascriptDelegate : public Awesomium::JSMethodHandler
{
private:
	//ref to parent
	AwesomiumHandler* _awesomium_handler;
	Awesomium::WebView* _web_view;

	//the global js objects with method callbacks
	int _delegate_remote_id;
public:

	/// Constructor.
	///
	/// @param [in,out]	awesomium_handler	If non-null, the awesomium handler.
	/// @param [in,out]	web_view		 	If non-null, the web view.
	JavascriptDelegate(AwesomiumHandler* awesomium_handler, Awesomium::WebView* web_view);

	/// Executes the method call action.
	/// @param [in,out]	caller  	If non-null, the caller.
	/// @param	remote_object_id	Identifier for the remote object.
	/// @param	method_name			Name of the method.
	/// @param	args				The arguments.
	virtual void OnMethodCall (Awesomium::WebView *caller, unsigned int remote_object_id, const Awesomium::WebString &method_name, const Awesomium::JSArray &args);

	/// Executes the method call with return value action./
	/// @param [in,out]	caller  	If non-null, the caller.
	/// @param	remote_object_id	Identifier for the remote object.
	/// @param	method_name			Name of the method.
	/// @param	args				The arguments.
	///
	/// @return	.
	virtual Awesomium::JSValue 	OnMethodCallWithReturnValue(Awesomium::WebView *caller, unsigned int remote_object_id, const Awesomium::WebString &method_name, const Awesomium::JSArray &args);
};

#endif  