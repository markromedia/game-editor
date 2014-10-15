#include "javascript_delegate.hpp"

#include "awesomium_handler.hpp"
#include "game.hpp"
#include "logger.hpp"

JavascriptDelegate::JavascriptDelegate(AwesomiumHandler* awesomium_handler, Awesomium::WebView* web_view) : _awesomium_handler(awesomium_handler), _web_view(web_view)
{
	Awesomium::JSValue delegate_value = _web_view->CreateGlobalJavascriptObject(Awesomium::WSLit("delegate"));
	Awesomium::JSObject& delegate_js_obj = delegate_value.ToObject();

	//save remote id
	_delegate_remote_id = delegate_js_obj.remote_id();

	//register callbacks
	delegate_js_obj.SetCustomMethod(Awesomium::WSLit("shrinkEntity"), false);
}

void JavascriptDelegate::OnMethodCall(Awesomium::WebView* caller, unsigned int remote_object_id, Awesomium::WebString const& method_name, Awesomium::JSArray const& args)
{
	if(remote_object_id != _delegate_remote_id)
	{
		return;
	}

	LOG_DEBUG("Got a javascript call");
}

Awesomium::JSValue JavascriptDelegate::OnMethodCallWithReturnValue(Awesomium::WebView* caller, unsigned remote_object_id, Awesomium::WebString const& method_name, Awesomium::JSArray const& args)
{
  return Awesomium::JSValue::Undefined();
}