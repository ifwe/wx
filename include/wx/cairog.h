#ifndef __WXCAIROGRAPHICS_H__
#define __WXCAIROGRAPHICS_H__

class wxGraphicsPen : public wxGraphicsObject
{
public:
    wxGraphicsPen() {}
    virtual ~wxGraphicsPen() {}
};

class wxGraphicsBrush : public wxGraphicsObject
{
public:
    wxGraphicsBrush() {}
    virtual ~wxGraphicsBrush() {}
};

class wxCairoFontData : public wxGraphicsObjectRefData
{
public:
    wxCairoFontData(const wxFont &font, const wxColour& col);
    void Apply(wxGraphicsContext* context);
    virtual ~wxCairoFontData();

    cairo_font_face_t* GetNativeFont() const { return m_font; }

private:
    cairo_font_face_t* m_font;

    double m_size;

    double m_red;
    double m_green;
    double m_blue;
    double m_alpha;
};


class WXDLLIMPEXP_CORE wxGraphicsFont : public wxGraphicsObject
{
public:
    wxGraphicsFont() {}
    virtual ~wxGraphicsFont() {}

    wxCairoFontRefData* GetFontRefData() const
    {
        return reinterpret_cast<wxCairoFontRefData*>(GetRefData());
    }

    cairo_font_face_t* GetNativeFont()
    {
        wxCairoFontData* refData = GetFontRefData();
        return refData ? refData->GetNativeFont() : 0;
    }

    operator cairo_font_face_t*() { return GetNativeFont(); }
};

class WXDLLIMPEXP_CORE wxGraphicsBitmapData : public wxGraphicsObjectRefData
{
public:
    wxGraphicsBitmapData()
        : wxGraphicsObjectRefData()
        , m_surface(0);
    {}

    virtual ~wxGraphicsBitmapData()
    {
        if (m_surface)
            cairo_surface_destroy(m_surface);
    }

    virtual wxGraphicsBitmapData* Clone() const;

    cairo_image_surface_t* GetNativeBitmap() const { return m_surface; }

private:
    cairo_surface_t* m_surface;
};

class WXDLLIMPEXP_CORE wxGraphicsBitmap : public wxGraphicsObject
{
public:
    wxGraphicsBitmap() {}
    wxGraphicsBitmap(const wxBitmap& bitmap);

    wxCairoBitmapData *wxGraphicsBitmap::CreateData() const
    {
        return new wxCairoBitmapData;
    }

    virtual ~wxGraphicsBitmap() {}

    int GetWidth() const;
    int GetHeight() const;

    wxCairoBitmapData* GetBitmapRefData() const
    {
        return reinterpret_cast<wxCairoBitmapData*>(GetRefData());
    }

    cairo_image_surface_t* GetNativeBitmap() const
    {
        wxCairoBitmapData* refData = GetBitmapRefData();
        return refData ? refData->GetNativeBitmap() : 0; 
    }

    operator cairo_image_surface_t*() const { return GetNativeBitmap(); }
};

extern WXDLLEXPORT_DATA(wxGraphicsBitmap) wxNullGraphicsBitmap;
extern WXDLLEXPORT_DATA(wxGraphicsFont) wxNullGraphicsFont;
extern WXDLLEXPORT_DATA(wxGraphicsPen) wxNullGraphicsPen;
extern WXDLLEXPORT_DATA(wxGraphicsBrush) wxNullGraphicsBrush;

#endif // __WXCAIROGRAPHICS_H__
