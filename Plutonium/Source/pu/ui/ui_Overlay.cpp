#include <pu/ui/ui_Overlay.hpp>
#include <pu/ui/ui_Application.hpp>
#include <cmath>

namespace pu::ui
{
    Overlay::Overlay(s32 X, s32 Y, s32 Width, s32 Height, Color Background, bool Rounded) : Container(X, Y, Width, Height)
    {
        this->bg = Background;
        this->round = Rounded;
        this->rad = 25;
        this->fadea = 0;
        this->end = false;
    }

    Overlay::~Overlay()
    {
        this->Clear();
    }

    void Overlay::SetRadius(s32 Radius)
    {
        this->rad = Radius;
    }

    s32 Overlay::GetRadius()
    {
        return this->rad;
    }

    void Overlay::OnPreRender(render::Renderer *Drawer)
    {
    }

    void Overlay::OnPostRender(render::Renderer *Drawer)
    {
    }

    bool Overlay::Render(render::Renderer *Drawer)
    {
        this->OnPreRender(Drawer);
        Drawer->SetBaseRenderAlpha(this->fadea);
        if(this->round) Drawer->RenderRoundedRectangleFill(this->bg, this->x, this->y, this->w, this->h, this->rad);
        else Drawer->RenderRectangleFill(this->bg, this->x, this->y, this->w, this->h);
        this->PreRender();
        if(!this->elms.empty()) for(s32 i = 0; i < this->elms.size(); i++)
        {
            elm::Element *elm = this->elms[i];
            if(elm->IsVisible()) elm->OnRender(Drawer);
        }
        Drawer->UnsetBaseRenderAlpha();
        if(this->end)
        {
            if(this->fadea > 0) this->fadea -= 25;
            else this->fadea = 0;
        }
        else
        {
            if(this->fadea < 200) this->fadea += 25;
            if(this->fadea > 200) this->fadea = 200;
        }
        this->OnPostRender(Drawer);
        bool fin = (this->end && (this->fadea == 0));
        if(fin)
        {
            this->end = false;
        }
        return !fin;
    }

    void Overlay::NotifyEnding(bool End)
    {
        this->end = End;
    }
}